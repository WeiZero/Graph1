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
	color = vec4(0,0,0,0);
	int n = 0;
	int half_size = 3;
	for (int i = -half_size; i <= half_size; ++i) {

		for (int j = -half_size; j <= half_size; ++j) {

			vec4 c = texture(screenTexture, TexCoords + vec2(i, j) / img_size);
			color += c;
			n++;
		}
	}
	color /= n;
}