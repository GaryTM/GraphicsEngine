#version 400
in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D diffuse;

struct LightInfo {
vec4 Position; // Light position in eye coords.
vec3 Intensity; // A,D,S intensity
};

uniform LightInfo Light;
struct MaterialInfo {
vec3 Ka; // Ambient reflectivity
vec3 Kd; // Diffuse reflectivity
vec3 Ks; // Specular reflectivity
float Shininess; // Specular shininess factor
};

uniform MaterialInfo Material;

layout( location = 0 ) out vec4 FragColor;

void phongModel( vec3 pos, vec3 norm, out vec3 ambient, out vec3 diffuse, out vec3 spec ) 
{
vec3 tnorm = normalize( NormalMatrix * VertexNormal);
vec4 eyeCoords = ModelViewMatrix *
vec4(VertexPosition,1.0);
vec3 s = normalize(vec3(Light.Position - eyeCoords));
vec3 v = normalize(-eyeCoords.xyz);
vec3 r = reflect( -s, tnorm );
vec3 ambient = Light.Intensity * Material.Ka;
float sDotN = max( dot(s,tnorm), 0.0 );
vec3 diffuse = Light.Ld * Material.Kd * sDotN;
vec3 spec = vec3(0.0);
if( sDotN > 0.0 )
spec = Light.Intensity * Material.Ks *
pow(max( dot(r,v), 0.0), Material.Shininess);
LightIntensity = ambient + diffuse + spec;
gl_Position = MVP * vec4(VertexPosition,1.0);
}

void main() {
vec3 ambient, diffuse, spec;

vec4 texColor = texture2D( diffuse, TexCoord );

phongModel(Position, Normal, ambient, diffuse, spec);

FragColor = vec4(ambAndDiff, 1.0) * texColor + vec4(spec, 1.0);

}