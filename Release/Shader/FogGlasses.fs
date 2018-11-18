#version 430

uniform sampler2D tex;

out vec4 vFragColor;

in vec2 TexCoords;

float rand(vec2 uv) {
 
    float a = dot(uv, vec2(92., 80.));
    float b = dot(uv, vec2(41., 62.));
    
    float x = sin(a) + cos(b) * 51.;
    return fract(x);
}

void main()
{
	vec2 uv = TexCoords;
	vec2 rnd = vec2(rand(uv), rand(uv));
    
    uv += rnd * .05;
    vFragColor = texture(tex, uv);
}