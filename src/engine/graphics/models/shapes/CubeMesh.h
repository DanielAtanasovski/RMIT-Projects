#pragma once

#include "../Mesh.h"

class CubeMesh : public Mesh {
public:
	CubeMesh();
	//void Draw(Shader& shader) override;
private:
	void CalculateBoxMesh();
};