#version 430
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float time;

float f(vec2 p) {
	float r = 100.0;
	int x = int(floor(p.x*r));
	int y = int(floor(p.y*r));
	int z = x * (x+7537) * (x+72642730) * (x-27628456) * y * int(time*100.0);
	int d = int(r);
	int e = z / d;
	return float(z - e*d)/r;
}
void main( void ) {

	vec2 p = TexCoords.xy;
	FragColor = vec4( vec3(f(p)), 1.0 ) * texture2D(screenTexture,TexCoords);
}