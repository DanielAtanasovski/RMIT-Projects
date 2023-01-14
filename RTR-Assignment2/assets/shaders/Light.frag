#version 330 core

struct Material {
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
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
uniform PointLight light;

out vec4 outFragColour;

void main() 
{
	outFragColour = vec4(1.0f);
}