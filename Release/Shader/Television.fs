#version 430
uniform float time;  
out vec4 vFragColor;
uniform sampler2D tex;

in vec2 TexCoords;

void main(){
    vec2 q = TexCoords;
    vec2 uv = 0.5 + (q-0.5)*(0.9 + 0.1*sin(0.2*time));

    vec3 oricol = texture( tex, vec2(q.x,q.y) ).xyz;
    vec3 col;

    col.r = texture(tex,vec2(uv.x+0.003,-uv.y)).x;
    col.g = texture(tex,vec2(uv.x+0.003,-uv.y)).y;
    col.b = texture(tex,vec2(uv.x+0.003,-uv.y)).z;

    col = clamp(col*0.5+0.5*col*col*1.2,0.0,1.0);

    col *= 0.5 + 0.5*16.0*uv.x*uv.y*(1.0-uv.x)*(1.0-uv.y);

    col *= vec3(0.95,1.05,0.95);

    col *= 0.9+0.1*sin(10.0*time+uv.y*1000.0);

    col *= 0.99+0.01*sin(110.0*time);

    col = mix( col, oricol, clamp(0.5,0.0,1.0) );

    vFragColor = vec4(col,1.0);
}