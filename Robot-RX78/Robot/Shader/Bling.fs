#version 430

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float time;

const float pi = 3.14159265;

float circle(vec2 coord, vec2 center, float r, float aperture)
{
  float x = coord.x - center.x, y = coord.y - center.y;
  float o = x * x + y * y - r * r;
  if(o<0)
    return 1; 
  return 1 - sqrt(o) / (r / aperture);
}

void main( void )
{
  float aperture = (sin(time*27.0) + 1.0) / 8.0 + .025;
  float radius = 0.1;
  vec2 center = vec2(0.5,0.5);
  
  FragColor = circle(TexCoords.xy, center, radius, aperture) * texture2D(screenTexture,TexCoords);
}