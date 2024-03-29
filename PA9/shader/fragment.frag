#version 330

in vec3 fN;
in vec3 fL;
in vec3 fE;

out vec4 frag_color;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;

uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 
uniform mat4 modelMatrix; 

uniform vec4 LightPosition;
uniform float Shininess;



void main()
{
	vec3 N = normalize( (viewMatrix*modelMatrix) * vec4(fN, 0.0) ).xyz;
	vec3 E = normalize(fE);
	vec3 L = normalize(fL);
	
	vec3 H = normalize(L + E);
	vec4 ambient = AmbientProduct;
	
	float Kd = max(dot(L,N), 0.0);
	vec4 diffuse = Kd*DiffuseProduct;
	
	float Ks = pow(max(dot(N,H), 0.0), Shininess);
	vec4 specular = Ks*SpecularProduct;
	
	if(dot(L,N) < 0.0)
	{
		specular = vec4(0.0, 0.0, 0.0, 1.0);
	}

	frag_color = (ambient + diffuse + specular);
	frag_color.a = 1.0;


}
