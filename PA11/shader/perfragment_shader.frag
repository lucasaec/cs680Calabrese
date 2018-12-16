#version 330

in vec3 fN;
in vec3 fL;
in vec3 fE;
smooth in vec2 uvs; 
in vec3 ipos;
out vec4 frag_color;

uniform vec4 LightPos[3];
uniform vec4 LAmbientProduct, LDiffuseProduct, LSpecularProduct;
uniform vec4 PAmbientProduct, PDiffuseProduct, PSpecularProduct;
uniform sampler2D gSampler;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;


uniform vec4 LightPosition;
uniform float Shininess;
uniform vec4 ballposition;
uniform float spot;
uniform float strength;
uniform float purpleStrength;
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
            fL =LightPos[0].xyz;
            
        
            L = normalize(fL);
            H = normalize(L + E);
            float dist = distance(LightPos[0],vec4(ipos,1));
            Kd = max(dot(L,N), 0.0)*9000/pow(dist,strength);
            Ks = pow(max(dot(N,H), 0.0), Shininess)*50/pow(dist,strength);
            if(dist > 30) {
                Kd = 0;
                Ks = 0;
            }
            if(dot(L,N) < 0) {
               Ks = 0;
               Kd = 0;  
            }
		specular += Ks*LSpecularProduct;
                diffuse += Kd*LDiffuseProduct;
  	    
                
                
        
        
         
	frag_color = (diffuse + ambient + specular)* texture2D(gSampler, uvs.xy);
	frag_color.a = opacity;
}

