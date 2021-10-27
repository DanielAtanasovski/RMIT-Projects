#version 330 core

#define MAX_LIGHTS 10

struct Material {
	vec3 Ambient;
	sampler2D Diffuse;
	sampler2D Specular;
	float Shininess;
};
uniform Material material;

struct PointLight {
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;

	vec3 Position;

	float Constant;
	float Linear;
	float Quadratic;
};
uniform int numLights;
uniform PointLight[MAX_LIGHTS] pLights;

struct DirectionalLight {
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Direction;
};
uniform DirectionalLight dLight;

uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 outFragColour;

vec3 CalcPointLight(PointLight pLight, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcDirLight(DirectionalLight dLight, vec3 normal, vec3 viewDir);

void main() 
{
	// Values
	vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

	// Directional light
	vec3 result = vec3(0.05); //CalcDirLight(dLight, norm, viewDir);

	// Point Lights
    for(int i = 0; i < numLights; i++) 
        result += CalcPointLight(pLights[i], norm, FragPos, viewDir);

	// Result
	outFragColour = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.Direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
    // combine results
    vec3 ambient = light.Ambient * texture(material.Diffuse, TexCoords).rgb;
    vec3 diffuse = light.Diffuse * diff * texture(material.Diffuse, TexCoords).rgb;
    vec3 specular = light.Specular * spec * texture(material.Specular, TexCoords).rgb;
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.Position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
    // attenuation
    float distance = length(light.Position - fragPos);
    float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.Ambient * texture(material.Diffuse, TexCoords).rgb;
    vec3 diffuse = light.Diffuse * diff * texture(material.Diffuse, TexCoords).rgb;
    vec3 specular = light.Specular * spec * texture(material.Specular, TexCoords).rgb;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}