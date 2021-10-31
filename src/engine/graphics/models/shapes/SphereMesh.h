#pragma once

#include "../Mesh.h"
// With help from http://www.songho.ca/opengl/gl_sphere.html

class SphereMesh : public Mesh {
public:
	SphereMesh(float radius, int sectors, int stacks);
	SphereMesh(float radius);
	void Recalculate(glm::vec3 scale) override;
private:
	void CalculateSphereMesh();

	const int MIN_SECTOR_COUNT = 32;
	const int MIN_STACK_COUNT = 8;
	int _sectors;
	int _stacks;
	float _radius = 1.0f;
};