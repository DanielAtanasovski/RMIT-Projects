#include "LightCube.h"
#include "../../engine/graphics/models/shapes/CubeMesh.h"

LightCube::LightCube(glm::vec3 position, std::shared_ptr<ResourceManager> resourceManager) 
	: Entity(Model(std::make_shared<CubeMesh>()), resourceManager->LoadShader(Shader("./assets/shaders/light.vert", "./assets/shaders/light.frag")))
{
	_position = position;

	_light = std::make_shared<PointLight>();
	_light->Position = _position;
	_light->Ambient = glm::vec3(0.2f);
	_light->Diffuse = glm::vec3(0.6f);
	_light->Specular = glm::vec3(1.0f);
	_light->Constant = 1.0f;
	_light->Linear = 0.0014f;
	_light->Quadratic = 0.000007f;
}

void LightCube::SetPosition(glm::vec3 position)
{
	_position = position;
	_light->Position = position;
}
