#version 400

struct LightInfo {
    vec4 Position;  // Light position in eye coords.
    vec3 La; // Ambient intensity
	vec3 Ld; // Diffuse intensity
	vec3 Ls; // Specular intensity
};

struct MaterialInfo {
    vec3 Ka;         // Ambient reflectivity
    vec3 Kd;         // Diffuse reflectivity
    vec3 Ks;         // Specular reflectivity
    float Shininess; // Specular shininess factor
};

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D diffuse;
uniform LightInfo Light;
uniform MaterialInfo Material;

void phongModel(vec3 pos, vec3 norm, out vec3 ambient, out vec3 diffuse, out vec3 spec) 
{
    vec3 tnorm = normalize(norm);
    vec4 eyeCoords = vec4(Position, 1);
    vec3 s = normalize(vec3(Light.Position - eyeCoords));
    vec3 v = normalize(-eyeCoords.xyz);
    vec3 r = reflect(-s, tnorm);
    ambient = Light.La * Material.Ka;
    float sDotN = max(dot(s, tnorm), 0);
    diffuse = Light.Ld * Material.Kd * sDotN;
    spec = vec3(0);
    if (sDotN > 0)
        spec = Light.Ls * Material.Ks * pow(max(dot(r, v), 0), Material.Shininess);
}

void main()
{
    vec3 ambientLight, diffuseLight, specularLight;
    phongModel(Position, Normal, ambientLight, diffuseLight, specularLight);

    vec4 texColor = texture(diffuse, TexCoord);

    FragColor = vec4(ambientLight + diffuseLight, 1) * texColor + vec4(specularLight, 1);
}