#include "SphereEntity.h"
#include "../utilities/ResourceManager.h"

SphereEntity::SphereEntity(std::shared_ptr<ResourceManager> resourceManager)
	: Entity(Model(std::make_shared<SphereMesh>(MIN_RADIUS)), resourceManager->LoadShader(Shader("./src/engine/graphics/shaders/Default.vert",
		"./src/engine/graphics/shaders/Default.frag")))
{
	Material material = {
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.3f, 0.3f, 0.3f),
		32.0f,
		0,
		0
	};
	_model.SetMaterial(material);
}

SphereEntity::SphereEntity(std::shared_ptr<ResourceManager> resourceManager, float radius) : Entity(Model(std::make_shared<SphereMesh>(radius)), resourceManager->LoadShader(Shader("./src/engine/graphics/shaders/Default.vert",
	"./src/engine/graphics/shaders/Default.frag")))
{
	Material material = {
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(0.3f, 0.3f, 0.3f),
	32.0f,
	0,
	0
	};
	_model.SetMaterial(material);
}

SphereEntity::SphereEntity(std::shared_ptr<ResourceManager> resourceManager, float radius, int sectors, int stacks) : Entity(Model(std::make_shared<SphereMesh>(radius, sectors, stacks)), resourceManager->LoadShader(Shader("./src/engine/graphics/shaders/Default.vert",
	"./src/engine/graphics/shaders/Default.frag")))
{
	Material material = {
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(0.3f, 0.3f, 0.3f),
	32.0f,
	0,
	0
	};
	_model.SetMaterial(material);
}
