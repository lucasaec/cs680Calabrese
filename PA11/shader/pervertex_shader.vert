#version 330
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 v_uvs;

out vec4 color;  
smooth out vec2 uvs;
     
uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 
uniform mat4 modelMatrix; 
uniform float spotlight_strength;
uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform vec4 LightPosition;
uniform float Shininess;
uniform sampler2D gSampler;
uniform vec4 ballposition;
uniform float spot;
uniform float spotlight_radius;
uniform float opacity;
const float strength = 30;

void main(void)
{
if(spot==1.0)
{
vec4 direction=normalize(ballposition-LightPosition);
	vec4 v=vec4(v_position,1.0);
    vec3 pos = ((viewMatrix*modelMatrix) * v).xyz;
vec3 campos=(inverse(viewMatrix)*vec4(0,0,0,1.0f)).xyz;
    vec3 L = normalize( LightPosition.xyz - (modelMatrix*vec4(v_position,1.0)).xyz );
    vec3 E = normalize( campos-pos );
	vec3 N = normalize(modelMatrix*vec4(v_normal,0.0)).xyz;
    
	vec3 H = normalize( L + E );
 

    // Compute terms in the illumination equation
    vec4 ambient = AmbientProduct;

    float Kd = max( dot(L, N), 0.0 );
    vec4  diffuse = Kd*DiffuseProduct;
    float Ks = pow( max(dot(N, H), 0.0),15 );
    vec4  specular = Ks * SpecularProduct;
    if( dot(L, N) < 0.0 )  
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
 gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v;
    color = ambient + diffuse + specular;
    color.a = opacity;
    uvs = v_uvs;
}
else
{
vec4 v=vec4(v_position,1.0);
    vec3 pos = ((viewMatrix*modelMatrix) * v).xyz;
vec3 campos=(inverse(viewMatrix)*vec4(0,0,0,1.0f)).xyz;
    vec3 L = normalize( LightPosition.xyz - (modelMatrix*vec4(v_position,1.0)).xyz );
    vec3 E = normalize( campos-pos );
	vec3 N = normalize(modelMatrix*vec4(v_normal,0.0)).xyz;
    
	vec3 H = normalize( L + E );
 

    // Compute terms in the illumination equation
    vec4 ambient = AmbientProduct;

    float Kd = max( dot(L, N), 0.0 );
    vec4  diffuse = Kd*DiffuseProduct;
    float Ks = pow( max(dot(N, H), 0.0),15 );
    vec4  specular = Ks * SpecularProduct;
    if( dot(L, N) < 0.0 )  
	{
	specular = vec4(0.0, 0.0, 0.0, 1.0); 
	 }

 gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v;
    color = ambient + diffuse + specular;
    color.a = opacity;
    uvs = v_uvs;
}
}
