#version 430 core                                                              

out vec4 vFragColor;
in vec2 TexCoords;

uniform sampler2D tex;         
                                  
void main()
{
	vec2 I=TexCoords;
    I = I - .5;
    vFragColor = texture(tex, .5 + I / sqrt(1. - 4. * dot(I,I)));
}