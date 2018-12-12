#version 330

in vec3 fN;
in vec3 fL;
in vec3 fE;
smooth in vec2 uvs; 
in vec3 ipos;
out vec4 frag_color;

uniform vec4 LightPos[3];
uniform vec4 LAmbientProduct, LDiffuseProduct, LSpecularProduct;

uniform sampler2D gSampler;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;


uniform float spotlight_strength;
uniform vec4 LightPosition;
uniform float Shininess;
uniform vec4 ballposition;
uniform float spot;
uniform float spotlight_radius;
uniform float strength;

uniform float opacity;

void main()
{

	vec3 N = normalize(fN);
	vec3 E = normalize(fE);
	
        vec3 fL=LightPosition.xyz;
        if(LightPosition.w!=0.0) {
            fL = LightPosition.xyz-fL; 
        }
        
        vec3 L = normalize(fL);
	
	vec3 H = normalize(L + E);
	vec4 ambient = AmbientProduct;
	
	float Kd = max(dot(L,N), 0.0);
	vec4 diffuse = Kd*DiffuseProduct;
	
	float Ks = pow(max(dot(N,H), 0.0), Shininess);
	vec4 specular = Ks*SpecularProduct;
	
     
	    if(dot(L,N) < 0.0) {
		specular = vec4(0.0, 0.0, 0.0, 1.0);
  	    }
          
            float dist = distance(LightPos[0],vec4(ipos,1));
            Kd = 100000/pow(dist,strength)/2;
            Ks = 500/pow(dist,strength);
            if(dist > 8) {
                Kd = 0;
            }
                diffuse += Kd*LDiffuseProduct;
                specular += Ks*LSpecularProduct;
        
        
         
	frag_color = (diffuse + ambient + specular)* texture2D(gSampler, uvs.xy);
	frag_color.a = opacity;
}

