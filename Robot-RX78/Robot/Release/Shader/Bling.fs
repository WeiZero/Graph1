#version 430

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float time;

void main( void )
{
  float aperture = (sin(time*27.0) + 1.0) / 8.0 + .025;

  
  FragColor = aperture * texture2D(screenTexture,TexCoords);
}