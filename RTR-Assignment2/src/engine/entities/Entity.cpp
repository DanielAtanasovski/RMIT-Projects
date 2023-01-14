#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>

void Entity::Draw()
{
	_shader->use();
	_shader->setMatrix4("modelMatrix", GetModelMatrix());
	_model.Draw(*_shader);
}

glm::mat4 Entity::GetModelMatrix()
{
	glm::mat4 result = glm::mat4(1);
	result = glm::translate(result, _position);
	result = glm::scale(result, _scale);

	// Different Rotations
	result = glm::rotate(result, glm::radians(_rotation.x), glm::vec3(1, 0, 0));
	result = glm::rotate(result, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
	result = glm::rotate(result, glm::radians(_rotation.z), glm::vec3(0, 0, 1));

	return result;
}
