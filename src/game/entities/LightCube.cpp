#include "LightCube.h"
#include "../../engine/graphics/models/shapes/CubeMesh.h"

LightCube::LightCube(glm::vec3 position) : Entity(CubeMesh(), Shader("./assets/shaders/light.vert","./assets/shaders/light.frag"))
{
	_position = position;
}
