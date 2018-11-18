#version 430
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float time;

// Plot a line on Y using a value between 0.0-1.0
float plot(vec2 st, float pct){
  return  smoothstep( pct-0.02, pct, st.y) -
          smoothstep( pct, pct+0.02, st.y);
}

void main() {
	vec2 st = TexCoords;

    float y = fract( sin(st.x * 10.0 + time * 20.0) * cos(0.3) / sin(0.0001) )+ 0.5;
	
    vec3 color = vec3(y);

    // Plot a line
    float pct = plot(st,y);
    color = (1.0-pct)*color+pct*vec3(1.5,1.0,0.0);

	FragColor = vec4(color * texture2D(screenTexture,TexCoords).rgb,1.0);
}
