#version 330

in vec3 fN;
in vec3 fL;
in vec3 fE;
smooth in vec2 uvs; 

out vec4 frag_color;

uniform sampler2D gSampler;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;

uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 
uniform mat4 modelMatrix; 
uniform float spotlight_strength;
uniform vec4 LightPosition;
uniform float Shininess;
uniform vec4 ballposition;
uniform float spot;
uniform float spotlight_radius;

uniform float opacity;

void main()
{
if(spot==1.0)
{
vec4 light=vec4(0.0,0.0,0.0,0.0);
vec4 direction=normalize(light-ballposition);
	vec3 N = normalize(fN);
	vec3 E = normalize(fE);
	
//vec3 fL=LightPosition.xyz;
//if(LightPosition.w!=0.0)
//{
//fL=LightPosition.xyz-fL;
//}

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



          if(acos(dot(-L,direction.xyz))>(0.525+spotlight_radius))
{
diffuse*=0;
specular*=0;
}
else
{
diffuse+=spotlight_strength;
specular+=spotlight_strength;
}

	frag_color = (diffuse + ambient + specular)* texture2D(gSampler, uvs.xy);
	frag_color.a = opacity;
}
else
{
	vec3 N = normalize(fN);
	vec3 E = normalize(fE);
	
vec3 fL=LightPosition.xyz;
if(LightPosition.w!=0.0)
{
fL=LightPosition.xyz-fL;
}

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
         
	frag_color = (diffuse + ambient + specular)* texture2D(gSampler, uvs.xy);
	frag_color.a = opacity;
}
}

