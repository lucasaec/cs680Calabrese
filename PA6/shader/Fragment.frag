#version 330

smooth in vec2 uvs; 

uniform sampler2D gSampler;


out vec4 frag_color; 

void main(void) 
{ 
frag_color = texture2D(gSampler, uvs.xy); 
} 

