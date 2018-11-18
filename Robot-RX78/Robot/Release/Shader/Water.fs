#version 430
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float time;

mat2 rotate(float a) {
	float c = cos(a),
		s = sin(a);
	return mat2(c, s, -s, c);
}

void main() {

	vec2 uv = TexCoords;//(2. * TexCoords.xy - vec2(0.5,0.5)) / 0.5;

	vec3 col = vec3(0., 0., -.1);
	vec3 ray = vec3(uv, 1.);
		
	float s = .5;
	for (int i = 0; i < 8; i++) {
		ray = abs(ray) / dot(ray, ray);
		ray -= s;
		ray.xy *= rotate(time * .1);
		ray.xz *= rotate(time * .1);
		ray.yz *= rotate(time * .1);
		s *= .95;
		col += .01 / max(abs(ray.x), abs(ray.y));
	}
	//col = abs(col-1);
	FragColor = vec4(col, 1.0) * texture2D(screenTexture,TexCoords);

}