#pragma once

#include "Entity.h"
#include "../utilities/ResourceManager.h"
#include "../graphics/models/shapes/SphereMesh.h"

class SphereEntity : public Entity {
public:
	SphereEntity(std::shared_ptr<ResourceManager> resourceManager);
	SphereEntity(std::shared_ptr<ResourceManager> resourceManager, float radius);
	SphereEntity(std::shared_ptr<ResourceManager> resourceManager, float radius, int sectors, int stacks);

private:
	const float MIN_RADIUS = 1.0f;
};