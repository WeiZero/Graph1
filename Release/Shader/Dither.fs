#version 410 core                                                              

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;                                           

void main(void)                                                                
{                                                                              
	vec4 texture_color = texture2D(screenTexture, TexCoords);							
	float grayscale_color = 0.299*texture_color.r + 0.587*texture_color.g + 0.114*texture_color.b;
	grayscale_color = step(0.5 , grayscale_color);
	FragColor = vec4(grayscale_color, grayscale_color, grayscale_color, 1.0);
}                                                                              
