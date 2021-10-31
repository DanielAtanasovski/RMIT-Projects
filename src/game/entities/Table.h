#pragma once

#include "../../engine/entities/Entity.h"
#include "../../engine/entities/CubeEntity.h"


class Table : public Entity{
public:
	Table(std::shared_ptr<ResourceManager> resourceManager);

	void Draw() override;
	void UpdateViewMatrix(glm::mat4 matrix);
	void UpdatePerspectiveMatrix(glm::mat4 matrix);
private:
	std::array<std::unique_ptr<CubeEntity>, 6> tableElements;
};