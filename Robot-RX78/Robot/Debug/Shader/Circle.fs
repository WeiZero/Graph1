#version 430
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float time;
uniform vec2 mouse;

float ntsf(float x,float k) {
	x = clamp(x,-1.0,1.0);
	float r = (x-x*k)/(k - abs(x) * 2.0 * k + 1.0);
	if(r < 0.00) {
		r=0.0;
	}
	return r;
}

void main( void ) {
	vec2 uv= TexCoords;
	float dx = uv.x-0.5;
 	float dy = uv.y-0.5;
	float d = sqrt(dx*dx+dy*dy);
 	float c = sin(ntsf(d,-0.5)*100.0-10.0*time);
	FragColor=vec4(vec3(c),1.0) * texture2D(screenTexture,TexCoords);
}