// Per-fragment interpolated values from the vertex shader

//Since normals are fixed for a given face of the cube in this example, fN per-fragment interpolation yields fixed values. Per-fragment interpolation of fL and fV however gives smoothly varying values through faces.

varying  vec3 fN;
varying  vec3 fL;
varying  vec3 fL2;
varying  vec3 fV;
varying  vec2 texCoord;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 ModelView;
uniform vec4 LightPosition;
uniform vec4 LightPosition2;
uniform float Shininess;
uniform int TextureFlag;
uniform int ModifiedPhongFlag;
uniform sampler2D texture;

void main()
{
    
    if (TextureFlag == 1){
        //sample a texture color from texture object
        //with newer versions of OpenGL you can  use texture() function instead of deprecated texture2D()
        gl_FragColor = texture2D( texture, texCoord );
        gl_FragColor.a = 1.0;
    } else {
        // Normalize the input lighting vectors
        vec3 N = normalize(fN);
        vec3 V = normalize(fV);
        vec3 L = normalize(fL);
        vec3 L2 = normalize(fL2);
        //vec3 R = vec3(0.0,0.0,0.0);
        if(ModifiedPhongFlag == 1){
            vec3 R = normalize( (2.0 * dot(L, N) * N) - L) ; // other phong
            vec3 H = normalize( L + V );
            
            vec4 ambient = AmbientProduct;
            
            float Kd = max(dot(L, N), 0.0);
            vec4 diffuse = Kd*DiffuseProduct;
            
            //if(ModifiedPhongFlag == 1) {
            float Ks = pow(max(dot(V, R), 0.0), Shininess); // other phong
            //} else {
            //float Ks = pow(max(dot(N, H), 0.0), Shininess);
            //}
            
            vec4 specular = Ks*SpecularProduct;
            
            // discard the specular highlight if the light's behind the vertex
            if( dot(L, N) < 0.0 ) {
                specular = vec4(0.0, 0.0, 0.0, 1.0);
            }
            
            gl_FragColor = ambient + diffuse + specular;
            gl_FragColor.a = 1.0;
            
        } else {
            vec3 H = normalize( L + V );
            vec3 H2 = normalize( L2 + V );
            
            vec4 ambient = AmbientProduct;
            
            float Kd = max(dot(L, N), 0.0);
            float Kd2 = max(dot(L2, N), 0.0);
            
            vec4 diffuse = Kd*DiffuseProduct;
            vec4 diffuse2 = Kd2*DiffuseProduct;
            
            float Ks = pow(max(dot(N, H), 0.0), Shininess);
            float Ks2 = pow(max(dot(N, H2), 0.0), Shininess);
            
            vec4 specular = Ks*SpecularProduct;
            vec4 specular2 = Ks2*SpecularProduct;
            
            // discard the specular highlight if the light's behind the vertex
            if( dot(L, N) < 0.0 ) {
                specular = vec4(0.0, 0.0, 0.0, 1.0);
            }
            
            if( dot(L2, N) < 0.0 ) {
                specular2 = vec4(0.0, 0.0, 0.0, 1.0);
            }
            
            gl_FragColor = (ambient + diffuse + specular) + (ambient + diffuse + specular2);
            gl_FragColor.a = 1.0;
        }
        
        
    }
    
    
    
    
}

