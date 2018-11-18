#version 430
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float time;
uniform vec2 mouse;

float circle(vec2 coord, vec2 center, float r, float aperture)
{
  float x = coord.x - center.x, y = coord.y - center.y;
  float o = x * x + y * y - r * r;
  if(o<0)
    return 1; 
  return 1 - sqrt(o) / (r / aperture);
}

void main( void ) {

    float aperture = 0.55;
    float radius = 0.1;
  
    FragColor = circle(TexCoords.xy, mouse, radius, aperture) * texture2D(screenTexture,TexCoords);
}