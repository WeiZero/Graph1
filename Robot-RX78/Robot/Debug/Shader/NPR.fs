#version 430
 
uniform vec2 img_size; 
out vec4 vFragColor; 
uniform sampler2D tex;

in vec2 TexCoords;

void main(){
	int a[20] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 };

	vec4 c[20]={
		vec4(0),vec4(0),vec4(0),vec4(0),vec4(0),
		vec4(0),vec4(0),vec4(0),vec4(0),vec4(0),
		vec4(0),vec4(0),vec4(0),vec4(0),vec4(0),
		vec4(0),vec4(0),vec4(0),vec4(0),vec4(0)};

				for (int x = -5; x <= 5; x++)
				{
					for (int y = -5; y <= 5; y++)
					{
						vec4 p1 = texture(tex, TexCoords + 0.001*vec2(x,y));
						int pi1 = int((p1.r + p1.g + p1.b)/3.0 * 19);
						a[pi1] ++;
						c[pi1] += p1;
					}
				}
				int index = 0;
				int max = a[0];
				for (int n = 0; n < 20; n++)
				{
					if (a[n] >= max)
					{
						max = a[n];
						index = n;
					}
				}
				vFragColor = c[index] / max;	
}