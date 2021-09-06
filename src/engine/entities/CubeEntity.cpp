#include "CubeEntity.h"

CubeEntity::CubeEntity() : Entity(CubeMesh(), Shader("./src/engine/graphics/shaders/Default.vert",
	"./src/engine/graphics/shaders/Default.frag"))
{
	Material material = {
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.3f, 0.3f, 0.3f),
		32.0f,
		glm::vec3(0)
	};
	_model.SetMaterial(material);
}
