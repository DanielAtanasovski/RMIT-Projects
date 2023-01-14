#pragma once
#include <glm/ext/vector_float3.hpp>

enum class LightType
{
	Directional,
	Point
};

class Light {
public:
	Light(LightType type, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		glm::vec3 direction, glm::vec3 position, float constant, float linear, float quadratic) 
	{
		_type = type;
		_ambient = ambient;
		_diffuse = diffuse;
		_specular = specular;
		_direction = direction;
		_position = position;
		_constant = constant;
		_linear = linear;
		_quadratic = quadratic;
	}

	LightType getType() { return _type; }
	glm::vec3 getAmbient() { return _ambient; }
	glm::vec3 getDiffuse() { return _diffuse; }
	glm::vec3 getSpecular() { return _specular; }
	glm::vec3 getDirection() { return _direction; }
	glm::vec3 getPosition() { return _position; }
	float getConstant() { return _constant; }
	float getLinear() { return _linear; }
	float getQuadratic() { return _quadratic; }

	void setDirection(glm::vec3 direction) {
		_direction = direction;
	}

protected:
	LightType _type;
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;
	glm::vec3 _direction;
	glm::vec3 _position;
	float _constant;
	float _linear;
	float _quadratic;

};