#pragma once

#include "../Mesh.h"

class CubeMesh : public Mesh {
public:
	CubeMesh();
	//void Draw(Shader& shader) override;
	void Recalculate(glm::vec3 scale) override;
private:
	void CalculateBoxMesh();
};