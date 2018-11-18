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
	vec4 texture_color = texture(screenTexture, TexCoords);

	float r = floor(texture_color.r * float(nbins)) / float(nbins);
	float g = floor(texture_color.g * float(nbins)) / float(nbins);
	float b = floor(texture_color.b * float(nbins)) / float(nbins);
	color = vec4(r, g, b, texture_color.a);
}