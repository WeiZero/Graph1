#version 430

out vec4 vFragColor;

in vec2 TexCoords;

uniform sampler2D image;
const vec2 TexSize = vec2(5689, 5689);
const vec2 mosaicSize = vec2(64, 64);

void main()
{
    vec2 intXY = vec2(TexCoords.x*TexSize.x, TexCoords.y*TexSize.y);
    vec2 XYMosaic = vec2(floor(intXY.x/mosaicSize.x)*mosaicSize.x, floor(intXY.y/mosaicSize.y)*mosaicSize.y);
    vec2 UVMosaic = vec2(XYMosaic.x/TexSize.x, XYMosaic.y/TexSize.y);
    vFragColor = texture(image, UVMosaic);
}