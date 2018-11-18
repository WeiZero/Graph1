#version 430

uniform float time;  
out vec4 vFragColor;
uniform sampler2D tex;

uniform vec2 img_size;

in vec2 TexCoords;

mat4 TransMatrix=mat4(
		0.7059,0.3529,0.5882,0.2353,
		0.0588,0.9412,0.8235,0.4118,
		0.4706,0.7647,0.8824,0.1176,
		0.1765,0.5294,0.2941,0.6471 );

void main(void)
{
	vec3 pixel=texture(tex,TexCoords).xyz;
	float gray = 0.3*pixel.x+0.59*pixel.y+0.11*pixel.z;
	
	if(gray > TransMatrix[int(TexCoords.x*img_size.x)%4][int(TexCoords.y*img_size.y)%4])
		vFragColor=vec4(1);
	else
		vFragColor=vec4(0);
}