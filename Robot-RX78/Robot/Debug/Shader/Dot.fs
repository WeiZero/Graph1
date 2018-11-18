#version 430 core                                                              

out vec4 vFragColor;
uniform vec2 img_size; 
in vec2 TexCoords;

uniform sampler2D tex;                                           

const float size = 7.0;

const float radius = size * 0.5 * 0.75;

void main()
{	
	float x=TexCoords.x*img_size.x;
	float y=TexCoords.y*img_size.y;
	vec2 quadPos = vec2(floor(x/size)*size,floor(y/size)*size);

	vec2 quadCenter = quadPos + vec2(size/2.0);

	float dist = length(quadCenter - TexCoords.xy*img_size.xy);
	
	vec3 texel = texture(tex, quadPos.xy/img_size.xy).rgb;

	if (dist > radius)
		vFragColor = vec4(vec3(0.25),1);
	else
		vFragColor = vec4(texel,1);
	
}