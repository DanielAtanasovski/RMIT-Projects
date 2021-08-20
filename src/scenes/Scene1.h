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

	glm::vec3 _currentColour = glm::vec3(1.0f);
	glm::vec3 _newColour = glm::vec3(1.0f);

	// Menger
	//std::vector<Cube*> _mengerCubesArray = std::vector<Cube*>();
	std::vector<glm::vec3> _verticesArray = std::vector<glm::vec3>();
	std::vector<glm::ivec3> _facesArray = std::vector<glm::ivec3>();

	glm::vec3 _position = glm::vec3(0);
	float _size = 5.0f;
	int _cubeCount = 0;

	const std::array<glm::vec3, 6> _CUBE_COLOURS = {
	glm::vec3(1.0f, 0.3f,  0.3f),
	glm::vec3(1.0f, 0.3f,  1.0f),
	glm::vec3(0.3f, 0.3f,  1.0f),
	glm::vec3(0.3f, 1.0f,  0.3f),
	glm::vec3(1.0f, 1.0f,  0.3f),
	glm::vec3(1.0f, 0.5f,  0.3f)
	};
};