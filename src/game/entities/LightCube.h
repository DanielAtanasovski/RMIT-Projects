#pragma once

#include "../../engine/entities/Entity.h"
#include "../../engine/graphics/models/Model.h"

class LightCube : public Entity  {
public:
	LightCube(glm::vec3 position);

	void SetColour(glm::vec3 colour) { _colour = colour; };
private:
	glm::vec3 _colour = glm::vec3(1.0f, 1.0f, 1.0f);
};