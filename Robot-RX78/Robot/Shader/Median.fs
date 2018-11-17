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
	int half_size = int(sqrt(SORT_SIZE)/2);
    vec4 sort_list[SORT_SIZE];
	int n = 0;
	for (int i = -half_size; i <= half_size; ++i) {
        for (int j = -half_size; j <= half_size; ++j) {
    		vec4 c = texture(screenTexture, TexCoords + vec2(i, j) / img_size);
			sort_list[n] = c;
			n++;
		}
	}

	for (int i = 0; i < SORT_SIZE; i++) {
		for (int j = SORT_SIZE - 1; i < j; j--) {
			float tmp_now = sort_list[j].r + sort_list[j].g + sort_list[j].b;
			float tmp_other = sort_list[j - 1].r + sort_list[j - 1].g + sort_list[j - 1].b;
			if (tmp_now < tmp_other) {
				vec4 tmp = sort_list[j];
				sort_list[j] = sort_list[j - 1];
				sort_list[j - 1] = tmp;
			}
		}
	}

	color = sort_list[SORT_SIZE/2];
}