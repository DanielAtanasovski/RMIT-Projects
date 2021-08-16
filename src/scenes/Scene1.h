#pragma once

#include "Scene.h"

class Scene1 : public Scene {
public:
	void Init() override;
	void Run() override;
	void Done() override;
	void Recalculate() override;
private:
	// Calculating Menger Sponge
	void CalculateMengerSponge(glm::vec3 position, float size, int subdivisions);
	void DrawMengerSpongeEfficient();
	void CalculateOuterLayer(float xMin, float xMax, float y, float zMin, float zMax, bool top);
	void CalculateMiddleLayer(float xMin, float xMax, float y, float zMin, float zMax);
	std::vector<CubeFaces> CalculateDisabledFaces(int row, int col, bool topLayer);

	// Menger
	std::vector<Cube*> _mengerCubesArray = std::vector<Cube*>();
	glm::vec3 _position = glm::vec3(0);
	float _size = 5.0f;
	int _cubeCount = 0;
};