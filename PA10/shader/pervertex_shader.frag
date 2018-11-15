#version 330
in vec4 color;
smooth in vec2 uvs; 
uniform sampler2D gSampler;
void main()
{
gl_FragColor = color +  texture2D(gSampler, uvs.xy);
}
