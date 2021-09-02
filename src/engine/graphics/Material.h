#pragma once

#include <glm/vec4.hpp>

struct Material {
	glm::vec4 Ambient;
	glm::vec4 Diffuse;
	glm::vec4 Specular;
	float Shininess;
	glm::vec4 Emission;
};