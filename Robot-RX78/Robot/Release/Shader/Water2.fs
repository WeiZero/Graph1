#version 430
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float time;
uniform vec2 mouse =vec2(1,1);

float Turb(vec2 p)
{

	vec2 i = p;
	float c = 0.0;
	float inten = 0.1;
	float r = length(p+vec2(sin(mouse.x),sin(mouse.y*0.433+2.))*3.);
	
	for (float n = 0.0; n < 1; n++) {
		float t = r-time * (1.0 - (1.9 / (n+1.)));
		      t = r-time/(n+0.6);
		i -= p + vec2(
			cos(t - mouse.y) + sin(t + i.y), 
			sin(t - mouse.x) + cos(t + i.x)+r
		);
		c += 1.0/length(vec2(
			(sin(i.x+t)/inten),
			(cos(i.y+t)/inten)
			)
		);
	
	}
	c /= float(1);
	c = clamp(c,-1.0,1.0);
	return c;
	
}

void main( void ) {

	vec2 p = TexCoords*24.0;
	float c = Turb(p);
	FragColor = vec4(vec3(c,c,c),1.0) * texture2D(screenTexture,TexCoords);
}