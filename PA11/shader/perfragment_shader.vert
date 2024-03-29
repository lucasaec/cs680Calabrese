#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 v_uvs;

out vec3 fN;
out vec3 fE;
out vec3 fL;
smooth out vec2 uvs;
out vec3 ipos;
uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 
uniform mat4 modelMatrix;

void main()
{

       vec3 pos=((viewMatrix * modelMatrix)*vPosition).xyz;
	vec3 campos=(inverse(viewMatrix)*vec4(0,0,0,1.0f)).xyz;
	fN = ((viewMatrix * modelMatrix)* vec4(vNormal,0.0)).xyz;
	fE = normalize(campos-pos);
	fL = (modelMatrix * vPosition).xyz;	
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vPosition;
        ipos = (modelMatrix * vPosition).xyz;
        uvs = v_uvs;

}
