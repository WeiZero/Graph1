#version 430
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float time;
uniform vec2 mouse;

void main( void ) {
  	vec2 sp = TexCoords;
  	vec2 p = sp * 15.0 - vec2(20.0);
  	vec2 i = p;
  	float c = 1.0;        // brightness; larger -> darker
  	float inten = 0.025;  // brightness; larger -> brighter
  	float speed = 0.1;    // larger -> slower
  	float speed2 = 0.1;   // larger -> slower
  	float freq = 0.5;     // ripples
  	float xflow = 0.1;    // flow speed in x direction
  	float yflow = 0.0;    // flow speed in y direction

  	for (int n = 0; n < 2; n++) {
    	float t = time * (1.0 - (3.0 / (float(n) + speed)));
    	i = p + vec2(cos(t - i.x * freq) + sin(t + i.y * freq), sin(t - i.y * freq) + cos(t + i.x * freq));
   		c += 1.0 / length(vec2(p.x / (sin(i.x + t * speed2) / inten), p.y / (cos(i.y + t * speed2) / inten)));
  	}
  
	c /= float(2);
	c = 1.5 - sqrt(c);
  	float v = c * c * c * c;
  	vec3 color = vec3(v, v + 0.4, v + 0.55);

	FragColor = vec4(color,1.0) * texture2D(screenTexture,TexCoords);
}