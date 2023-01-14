#pragma once
#include <glm/ext/vector_float3.hpp>

struct DirectionalLight {
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	glm::vec3 Direction;
};

struct PointLight {
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;

	glm::vec3 Position;

	float Constant;
	float Linear;
	float Quadratic;
};