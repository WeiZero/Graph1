#version 430

out vec4 vFragColor;

in vec2 TexCoords;

uniform sampler2D image;

const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);
const vec2 TexSize = vec2(100.0, 100.0);
const vec4 bkColor = vec4(0.5, 0.5, 0.5, 1.0);

void main()
{
    vec2 upLeftUV = vec2(TexCoords.x-1.0/TexSize.x, TexCoords.y-1.0/TexSize.y);
    vec4 curColor = texture(image, TexCoords);
    vec4 upLeftColor = texture(image, upLeftUV);
    vec4 delColor = curColor - upLeftColor;
    float luminance = dot(delColor.rgb, W);
    vFragColor = vec4(vec3(luminance), 0.0) + bkColor;
}