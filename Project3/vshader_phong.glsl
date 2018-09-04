attribute   vec4 vPosition;
attribute   vec3 vNormal;
attribute  vec2 vTexCoord;

// output values that will be interpretated per-fragment
varying  vec3 fN;
varying  vec3 fV;
varying  vec3 fL;
varying  vec3 fL2;
varying vec2 texCoord;

uniform mat4 ModelView;
uniform vec4 LightPosition;
uniform vec4 LightPosition2;
uniform mat4 Projection;

void main()
{
    // Transform vertex position into camera (eye) coordinates
    vec3 pos = (ModelView * vPosition).xyz;
    
    fN = (ModelView * vec4(vNormal, 0.0)).xyz; // normal direction in camera coordinates
    
    fV = -pos; //viewer direction in camera coordinates
    
    fL = LightPosition.xyz; // light direction
    
    fL2 = LightPosition2.xyz;
    
    if( LightPosition.w != 0.0 ) {
        fL = LightPosition.xyz - pos;  //directional light source
    }
    
    if( LightPosition2.w != 0.0 ) {
        fL2 = LightPosition2.xyz - pos;  //directional light source
    }
    
    texCoord    = vTexCoord;
    gl_Position = Projection * ModelView * vPosition;
}
