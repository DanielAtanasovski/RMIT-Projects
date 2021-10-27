#include "LightCube.h"
#include "../../engine/graphics/models/shapes/CubeMesh.h"

LightCube::LightCube(glm::vec3 position, std::shared_ptr<ResourceManager> resourceManager) 
	: Entity(CubeMesh(), resourceManager->LoadShader(Shader("./assets/shaders/light.vert", "./assets/shaders/light.frag")))
{
	_position = position;

	_light = std::make_shared<PointLight>();
	_light->Position = _position;
	_light->Ambient = glm::vec3(0.4f);
	_light->Diffuse = glm::vec3(0.5f);
	_light->Specular = glm::vec3(1.0f);
}

void LightCube::SetPosition(glm::vec3 position)
{
	_position = position;
	_light->Position = position;
}
