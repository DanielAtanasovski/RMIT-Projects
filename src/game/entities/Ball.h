#pragma once

#include "../../engine/entities/Entity.h"
#include "../../engine/utilities/ResourceManager.h"

class Ball : public Entity {
public:
	Ball(glm::vec3 position, std::shared_ptr<ResourceManager> resourceManager);
};