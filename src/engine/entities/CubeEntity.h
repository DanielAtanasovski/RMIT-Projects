#pragma once

#include "Entity.h"
#include "../graphics/models/shapes/CubeMesh.h"

class CubeEntity : public Entity {
public:
	CubeEntity() : Entity(CubeMesh(), Shader("./src/engine/graphics/shaders/Default.vert",
		"./src/engine/graphics/shaders/Default.frag")) {};
private:

};