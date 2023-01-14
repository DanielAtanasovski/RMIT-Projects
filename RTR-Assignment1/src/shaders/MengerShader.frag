#version 330 core

// With the help of learnopengl.com
#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1
#define MAX_LIGHTS 10
#define MATERIAL_COUNT 3

struct Material {
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Emission;
	float Shininess;
};

struct Light {
	int Type;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Direction;
	vec3 Position;
	float Constant;
	float Linear;
	float Quadratic;
};

// In
flat in int MaterialID;
in vec3 geomNormal;
in vec3 fragPos;

// Uniform
uniform Material materials[MATERIAL_COUNT];
uniform Light Lights[MAX_LIGHTS];
uniform int NumberOfLights;
uniform mat4 modelMatrix;
uniform bool lightingEnabled;
uniform bool directionalEnabled;

// Out
out vec4 FragColor;

// Light Functions
vec3 CalculateDirectionalLight(Light light, vec3 normal, vec3 viewDirection, Material mat);
vec3 CalculatePointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDirection, Material mat);

void main()
{
	Material mat = materials[MaterialID];
	vec3 result = vec3(0);
	vec3 norm = normalize(geomNormal);
	
	if (lightingEnabled) {
		// Props

		vec3 viewDir = normalize(Lights[0].Position - fragPos);

		// Directional
		if (directionalEnabled)
			result = CalculateDirectionalLight(Lights[0], norm, viewDir, mat);

		// Point Lights (Skip first as that is directional)
		for (int i = 1; i < NumberOfLights; i++) {
			result += CalculatePointLight(Lights[i], norm, fragPos, viewDir, mat);
		}
	} else {
		result = mat.Ambient * mat.Diffuse;
	}


//	FragColor.xyz += abs(norm.xyz); Debug
	FragColor = vec4(result, 1.0);
}


vec3 CalculateDirectionalLight(Light light, vec3 normal, vec3 viewDirection, Material mat) {

	vec3 lightDirection = normalize(-light.Direction);

	// Diffuse
	float diff = max(dot(normal, lightDirection), 0.0);

	// Specular
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), mat.Shininess);

	// Combination
	vec3 ambient = light.Ambient * mat.Ambient;
	vec3 diffuse = light.Diffuse * diff * mat.Diffuse;
	vec3 specular = light.Specular * spec * mat.Specular;
	return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDirection, Material mat) {

	vec3 lightDirection = normalize(light.Position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDirection), 0.0);

    // specular shading
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), mat.Shininess);

    // attenuation
    float distance    = length(light.Position - fragPos);
    float attenuation = 1.0 / (light.Constant + light.Linear * distance + 
  			     light.Quadratic * (distance * distance));    

    // combine results
    vec3 ambient  = light.Ambient  * mat.Ambient;
    vec3 diffuse  = light.Diffuse  * diff * mat.Diffuse;
    vec3 specular = light.Specular * spec * mat.Specular;

	// Set Range
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}