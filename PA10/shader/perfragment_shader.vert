#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 v_uvs;

out vec3 fN;
out vec3 fE;
out vec3 fL;
out vec3 frag_pos;

uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 
uniform mat4 modelMatrix;

uniform vec4 LightPosition;

smooth out vec2 uvs;

void main()
{
       
	fN = vNormal;
	fE = vPosition.xyz;
	fL = LightPosition.xyz;
	
	if(LightPosition.w != 0.0)
	{
		fL = LightPosition.xyz - vPosition.xyz;
	}
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vPosition;
        frag_pos = (viewMatrix*modelMatrix*vPosition).xyz;
        uvs = v_uvs;
}
