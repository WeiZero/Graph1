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
    vec2 coord1 = TexCoords + vec2(-3.0, -3.0) / img_size;
	vec2 coord2 = TexCoords + vec2(-3.0, 3.0) / img_size;
	vec2 coord3 = TexCoords + vec2(3.0, -3.0) / img_size;
	vec2 coord4 = TexCoords + vec2(3.0, 3.0) / img_size;

	vec4 s1 = vec4(texture2D(screenTexture, coord1));
	vec4 s2 = vec4(texture2D(screenTexture, coord2));
	vec4 s3 = vec4(texture2D(screenTexture, coord3));
	vec4 s4 = vec4(texture2D(screenTexture, coord4));

	vec4 tmp1 = mix(s1, s3, TexCoords.x);
	vec4 tmp2 = mix(s2, s4, TexCoords.x);

	color = mix(tmp1, tmp2, TexCoords.y);
}