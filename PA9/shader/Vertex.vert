
attribute vec4 v_position;
attribute vec3 v_normal;


varying vec4 color;  
     
uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 
uniform mat4 modelMatrix; 



uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;


uniform vec4 LightPosition;
uniform float Shininess;


void main(void)
{


    
    vec3 pos = ((viewMatrix * modelMatrix) * v_position).xyz;
	
    vec3 L = normalize( LightPosition.xyz - pos );
    vec3 E = normalize( -pos );
    vec3 H = normalize( L + E );

    // Transform vertex normal into eye coordinates
    vec3 N = normalize( (viewMatrix*modelMatrix) * vec4(v_normal, 0.0) ).xyz;

    // Compute terms in the illumination equation
    vec4 ambient = AmbientProduct;

    float Kd = max( dot(L, N), 0.0 );
    vec4  diffuse = Kd*DiffuseProduct;
    float Ks = pow( max(dot(N, H), 0.0), Shininess );
    vec4  specular = Ks * SpecularProduct;
    if( dot(L, N) < 0.0 )  specular = vec4(0.0, 0.0, 0.0, 1.0); 

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v_position;

  
    color = ambient + diffuse + specular;
    color.a = 1.0;

}
