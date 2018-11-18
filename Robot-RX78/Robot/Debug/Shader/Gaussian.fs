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
	int half_size = int(MASK_SIZE/2);
	int mask[MASK_SIZE];
	mask[0] = 1;
	for (int i = 1; i<MASK_SIZE; i++) {
	    int a = MASK_SIZE - 1;
		int b = 1;
		int tmp_a = a;
		int tmp_b = b;
		for (int j = 1; j<i; j++) {
			a = a * (tmp_a - j);
			b = b * (tmp_b + j);
		}
		mask[i] = a / b;
	}

	for (int i = -half_size; i <= half_size; ++i) {
		for (int j = -half_size; j <= half_size; ++j) {
			vec4 c = texture(screenTexture, TexCoords + vec2(i, j) / img_size) * mask[i+ half_size] * mask[j+ half_size];
			color += c;
		}
	}
	color /= (pow(2, MASK_SIZE-1)*pow(2, MASK_SIZE - 1));
}