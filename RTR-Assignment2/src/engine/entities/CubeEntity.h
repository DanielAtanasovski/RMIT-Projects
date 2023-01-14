#pragma once

#include "Entity.h"
#include "../utilities/ResourceManager.h"
#include "../graphics/models/shapes/CubeMesh.h"

class CubeEntity : public Entity {
public:
	CubeEntity(std::shared_ptr<ResourceManager> resourceManager);

};