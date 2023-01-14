#pragma once

#include <glm/vec4.hpp>

struct Material {
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Shininess;
	unsigned int DiffuseID;
	unsigned int SpecularID;
};