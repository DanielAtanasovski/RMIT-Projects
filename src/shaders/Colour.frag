#version 330 core

struct Material {
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Emission;
	float shininess;
};

flat in int MaterialID;
out vec4 FragColor;

#define MATERIAL_COUNT 3

uniform Material materials[MATERIAL_COUNT];

void main()
{
	Material mat = materials[MaterialID];
	// Ambient
	vec3 a = mat.Ambient;

	// Diffuse
	vec3 d = mat.Diffuse;
//	if (ourMaterialID == 0) {
//		FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	} 
//	else if (ourMaterialID == 1) {
//		FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
//	} 
//	else if (ourMaterialID == 2) {
//		FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	}

	FragColor = vec4(normalize(a * d), 1.0f);
}