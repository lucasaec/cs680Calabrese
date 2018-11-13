#version 330

in vec4 vPosition;
in vec3 vNormal;

out vec3 fN;
out vec3 fE;
out vec3 fL;
out vec3 frag_pos;

uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 
uniform mat4 modelMatrix;

uniform vec4 LightPosition;



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
        frag_pos = (viewMatrix * zmodelMatrix *  vPosition).xyz;
}
