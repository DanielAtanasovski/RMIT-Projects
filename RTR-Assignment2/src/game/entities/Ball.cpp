#include "Ball.h"

#include "../../engine/graphics/models/shapes/SphereMesh.h"

Ball::Ball(glm::vec3 position, std::shared_ptr<ResourceManager> resourceManager)
	: Entity(Model(std::make_shared<SphereMesh>(0.5f)), resourceManager->LoadShader(Shader("./assets/shaders/Standard.vert", "./assets/shaders/Standard.frag")))
{
	_position = position;

	SetMaterial({
	glm::vec3(0.4f),
	glm::vec3(0),
	glm::vec3(0.1f),
	32.0f,
	resourceManager->LoadTexture("./assets/textures/marble.png"),
	0
	}, true, false);
}