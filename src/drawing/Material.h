#pragma once

#include <glm/vec4.hpp>

class Material {
public:
	Material(glm::vec4 ambient, glm::vec4 diffuse,
		glm::vec4 specular, glm::vec4 shininess, glm::vec4 emission) {
		_ambient = ambient;
		_diffuse = diffuse;
		_specular = specular;
		_shininess = shininess;
		_emission = emission;
	}

	glm::vec4 GetAmbient() { return _ambient; }
	glm::vec4 GetDiffuse() { return _diffuse; }
	glm::vec4 GetSpecular() { return _specular; }
	glm::vec4 GetShininess() { return _shininess; }
	glm::vec4 GetEmission() { return _emission; }
private:
	glm::vec4 _ambient;
	glm::vec4 _diffuse;
	glm::vec4 _specular;
	glm::vec4 _shininess;
	glm::vec4 _emission;
};