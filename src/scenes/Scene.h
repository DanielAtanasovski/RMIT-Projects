#pragma once

#include <vector>
#include "../drawing/Shapes.h"
#include "../drawing/HUD.h"
#include "../Camera.h"

class Scene
{
public:
	// Scene
	Scene() {};
	~Scene() {};
	virtual void Init(HUD* hud, Camera* camera) = 0; // Initialise
	virtual void Update(unsigned int td_milli) = 0; // Use to update with delta
	virtual void Run() = 0; // Loop
	virtual void Done() = 0; // Unbind stuff
	virtual void Recalculate();

	// Toggles
	void ToggleLighting();
	bool isLighting() { return _lighting; }
	void ToggleCullFaces();
	bool isCulling() { return _cullFaces; }
	void ToggleDepthTest();
	bool isDepthTesting() { return _depthTest; }

	// Getters / Setters
	int GetSubdivisions() { return _subdivisions; }
	void SetSubdivisions(int subdivisions) { _subdivisions = subdivisions; };

protected:
	HUD* _hud = nullptr;
	Camera* _camera = nullptr;

	// Settings
	int _subdivisions = 0;
	bool _cullFaces = true;
	bool _depthTest = true;
	bool _lighting = false;
	size_t _triangleCount = 0;
	int _cubeCount = 0;

	// Matrix
	glm::mat4 _modelMatrix = glm::mat4(1);

	// Calculating Menger Sponge
	void CalculateMengerSponge(glm::vec3 position, float size, int subdivisions);
	virtual void Draw() {};

	// Menger Sponge Arrays
	std::vector<glm::vec3> _verticesArray = std::vector<glm::vec3>();
	std::vector<glm::ivec3> _facesArray = std::vector<glm::ivec3>();
	std::vector<int> _materialIds = std::vector<int>();

	glm::vec3 _position = glm::vec3(0);
	float _size = 10.0f;

private:
	void CalculateOuterLayer(float xMin, float xMax, float y, float zMin, float zMax, bool top);
	void CalculateMiddleLayer(float xMin, float xMax, float y, float zMin, float zMax);
	std::vector<CubeFaces> CalculateDisabledFaces(int row, int col, bool topLayer);
	void PruneVertices();
};