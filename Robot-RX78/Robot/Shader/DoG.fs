#version 410

uniform sampler2D screenTexture; 
uniform vec2 img_size; 
out vec4 color; 

in vec2 TexCoords;

float sigma_e = 2.0f; 
float sigma_r = 2.8f; 
float phi = 3.4f; 
float tau = 0.99f; 
float twoSigmaESquared = 2.0 * sigma_e * sigma_e;		
float twoSigmaRSquared = 2.0 * sigma_r * sigma_r;		
int halfWidth = int(ceil(2.0 * sigma_r)); 

int nbins = 8; 

#define SORT_SIZE  49  
#define MASK_SIZE  7

void main(void)
{
    vec2 sum = vec2(0.0); 
	vec2 norm = vec2(0.0); 
	int kernel_count = 0; 
	for (int i = -halfWidth; i <= halfWidth; ++i) {
		for (int j = -halfWidth; j <= halfWidth; ++j) {
			float d = length(vec2(i, j)); 
			vec2 kernel = vec2(exp(-d * d / twoSigmaESquared), 
			exp(-d * d / twoSigmaRSquared)); 
			vec4 c = texture(screenTexture, TexCoords + vec2(i, j) / img_size); 
			vec2 L = vec2(0.299 * c.r + 0.587 * c.g + 0.114 * c.b); 
				
			norm += 2.0 * kernel; 
			sum += kernel * L; 
		}
	}
	sum /= norm; 

	float H = 100.0 * (sum.x - tau * sum.y); 
	float edge = (H > 0.0) ? 1.0 : 2.0 * smoothstep(-2.0, 2.0, phi * H); 

	color = vec4(edge, edge, edge, 1.0);
}