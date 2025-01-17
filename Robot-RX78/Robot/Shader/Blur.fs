#version 410 core     
 
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;      
 
const vec2 sketchSize = vec2(512., 512.);
const float barrelPower = 0.4; 
const int num_iter = 10;
const float reci_num_iter_f = 1.0 / float(num_iter); // 用于迭代时归一化
 
vec2 barrelDistortion(vec2 coord, float amt) // 随着迭代次数增加，像素偏移更大；距离图像中心越远，像素偏移更大。
{
    vec2 cc = coord - 0.5;
    float dist = dot(cc, cc);
    return coord + cc * dist * amt; 
}
 
float sat( float t )
{
    return clamp( t, 0.0, 1.0 );
}
 
float linterp( float t ) {
    return sat( 1.0 - abs( 2.0*t - 1.0 ) );
}
 
float remap( float t, float a, float b ) 
{
    return sat( (t - a) / (b - a) );
}
 
vec3 spectrum_offset( float t ) 
{
    vec3 ret;
    float lo = step(t,0.5);
    float hi = 1.0-lo;
    float w = linterp( remap( t, 1.0/6.0, 5.0/6.0 ) );
    ret = vec3(lo,1.0,hi) * vec3(1.0-w, w, 1.0-w);
 
    return pow( ret, vec3(1.0/2.2) );
}
 
void main()
{   
    vec2 uv = TexCoords;
 
    vec3 sumcol = vec3(0.0);
    vec3 sumw = vec3(0.0);  
    for ( int i=0; i<num_iter;++i )
    {
        float t = float(i) * reci_num_iter_f;
        vec3 w = spectrum_offset( t );   // RGB三通道分别的权重
        sumw += w;                       // 用于之后归一化权重
		uv = barrelDistortion(uv, barrelPower*t );
        sumcol += w * texture2D( screenTexture, uv).rgb; 
    } 
        
    FragColor = vec4(sumcol.rgb / sumw, 1.0);
}