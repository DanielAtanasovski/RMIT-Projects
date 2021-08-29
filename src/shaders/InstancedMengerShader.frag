#version 330 core

struct Material {
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Emission;
	float Shininess;
};

// Lighting
#define DirectionalLight 0
#define PointLight 1

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

#define MAX_LIGHTS 10
uniform Light Lights[MAX_LIGHTS];
uniform int NumberOfLights;

#define MATERIAL_COUNT 3
uniform Material materials[MATERIAL_COUNT];

flat in int MaterialID;
in mat4 modelMatrix;
in vec3 outNormal;
in vec3 FragPos;

out vec4 FragColor;

// Light Functions
vec3 CalculateDirectionalLight() {
	return vec3(0);
}

vec3 CalculatePointLight() {
	return vec3(0);
}

void main()
{
	Material mat = materials[MaterialID];

	// Ambient
	vec3 a = mat.Ambient * Lights[0].Ambient;

	// Diffuse
	vec3 norm = normalize(mat3(transpose(inverse(modelMatrix))) * outNormal);
	vec3 lightDirection = normalize(Lights[0].Direction);

	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 d = Lights[0].Diffuse * (diff * mat.Diffuse);

	// Specular
//	vec3 lightDir = normalize(Lights[0].Position - FragPos);
//	vec3 viewDir = normalize(-Lights[0].Direction);
//	vec3 halfwayDir = normalize(lightDir + viewDir);
//	vec3 reflectDirection = reflect(lightDirection, norm);
//	float spec = pow(max(dot(viewDir, reflectDirection), 0.0), mat.Shininess);
//	vec3 s = Lights[0].Specular * (spec * mat.Specular);

	vec3 result = a;
	FragColor = vec4(result, 1.0);
}