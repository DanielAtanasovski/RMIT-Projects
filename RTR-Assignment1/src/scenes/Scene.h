#pragma once

#include <vector>
#include "../drawing/Shapes.h"
#include "../drawing/HUD.h"
#include "../Camera.h"
#include "../drawing/Light.h"

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
	int GetLightCount() { return _numLights; }
	virtual void SetLightCount(int count) = 0;
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
	virtual void SetupLights() = 0;

	// Menger Sponge Arrays
	std::vector<glm::vec3> _verticesArray = std::vector<glm::vec3>();
	std::vector<glm::ivec3> _facesArray = std::vector<glm::ivec3>();
	std::vector<int> _materialIds = std::vector<int>();

	glm::vec3 _position = glm::vec3(0);
	float _size = 10.0f;

	// Lights
	int _numLights = 0;
	bool _directional = false;
	float _lightPositionOffset = 0;

	// Debug Colours
	const std::array<glm::vec3, 5> _Colours = {
		glm::vec3(1.0, 0.0, 0.0), // RED
		glm::vec3(0.0, 1.0, 0.0), // GREEN
		glm::vec3(0.0, 0.0, 1.0), // BLUE
		glm::vec3(1.0, 1.0, 0.0), // YELLOW
		glm::vec3(1.0, 1.0, 1.0), // WHITE
	};

	//				Type,					Ambient,				      Diffuse,					Specular,		Direction, Position, Constant, Linear, Quadratic
	std::array<Light, 8> _lights = {
		Light(LightType::Directional, _Colours[4] * glm::vec3(1), glm::vec3(0.4, 0.4, 0.4), glm::vec3(0.4, 0.4, 0.4), glm::vec3(0, 0, 1), glm::vec3(0),                                 0, 0, 0),
		Light(LightType::Point,       _Colours[2] * glm::vec3(0.4), glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.3, 0.3, 0.3), glm::vec3(0),       glm::vec3(_size + _lightPositionOffset, 0, 0), 1.0f, 0.09, 0.032),
		Light(LightType::Point,       _Colours[1] * glm::vec3(0.4), glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.3, 0.3, 0.3), glm::vec3(0),       glm::vec3(-_size - _lightPositionOffset, 0, 0), 1.0f, 0.09, 0.032),
		Light(LightType::Point,       _Colours[0] * glm::vec3(0.4), glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.3, 0.3, 0.3), glm::vec3(0),       glm::vec3(0, _size + _lightPositionOffset, 0), 1.0f, 0.09, 0.032),
		Light(LightType::Point,       _Colours[3] * glm::vec3(0.4), glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.3, 0.3, 0.3), glm::vec3(0),       glm::vec3(0, -_size - _lightPositionOffset, 0), 1.0f, 0.09, 0.032),
		Light(LightType::Point,       _Colours[4] * glm::vec3(0.4), glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.3, 0.3, 0.3), glm::vec3(0),       glm::vec3(0, 0, _size + _lightPositionOffset), 1.0f, 0.09, 0.032),
		Light(LightType::Point,       _Colours[3] * glm::vec3(0.4), glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.3, 0.3, 0.3), glm::vec3(0),       glm::vec3(0, 0, -_size - _lightPositionOffset), 1.0f, 0.09, 0.032),
		Light(LightType::Point,       _Colours[1] * glm::vec3(0.4), glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.3, 0.3, 0.3), glm::vec3(0),       glm::vec3(0, _size + _lightPositionOffset, -_size - _lightPositionOffset), 1.0f, 0.09, 0.032),
	};

private:
	void CalculateOuterLayer(float xMin, float xMax, float y, float zMin, float zMax, bool top);
	void CalculateMiddleLayer(float xMin, float xMax, float y, float zMin, float zMax);
	std::vector<CubeFaces> CalculateDisabledFaces(int row, int col, bool topLayer);
	void PruneVertices();
};