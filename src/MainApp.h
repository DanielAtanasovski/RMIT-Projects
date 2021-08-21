// Daniel Atanasovski
#pragma once

#include "App.h"
#include "util/Input.h"
#include "Camera.h"
#include "drawing/Shapes.h"
#include <vector>
#include "scenes/Scene1.h"
#include "drawing/HUD.h"

// Macros
#define FPSSAMPLES 100

class MainApp : public App
{
public:
	MainApp(const char* title, bool fullscreen = false, int width = 1024, int height = 768)
		: App(title, fullscreen, width, height) {};
	int Init();
	void Done();
	bool Tick(unsigned int td_milli);
	HUD& getHUD() { return *_hud; }
private:
	bool _quitApp = false;

	// --- First Attempt Legacy ---
	//void DrawMengerSponge(glm::vec3 position, float size, int subdivisions);
	//void CalculateMengerSponge(glm::vec3 position, float size, int subdivisions);
	//void DrawMengerSpongeEfficient();
	//void CalculateOuterLayer(float xMin, float xMax, float y, float zMin, float zMax, bool top);
	//void CalculateMiddleLayer(float xMin, float xMax, float y, float zMin, float zMax);
	//std::vector<CubeFaces> CalculateDisabledFaces(int row, int col, bool topLayer);
	//void DrawOuterLayer(float xMin, float xMax, float y, float zMin, float zMax);
	//void DrawMiddleLayer(float xMin, float xMax, float y, float zMin, float zMax);
	//void DrawCenteredCube(float x, float y, float z, float size); // todo: move to renderer class?
	//void DrawCube(float minX, float minY, float minZ, float maxX, float maxY, float maxZ); // todo: move to renderer class?
	
	void CheckInput();
	void CheckEvents();
	void Update(unsigned int td_milli);
	void Draw();
	//double CalculateF(int delta);

	// fps
	int _fps = 0;
	int _timeCount = 0;

	Camera *_camera = nullptr;
	HUD *_hud = nullptr;
	Input *_input = nullptr;

	std::array<Scene*, 1> _scenes = { new Scene1( ) };
	int _currentScene = 0;
	//std::vector<Cube*> _mengerCubesArray = std::vector<Cube*>();

	// Camera Controls 
	// todo: move to camera class
	glm::vec3 _inputDirection = glm::vec3(0);
	float _cameraSpeed = 5.0f;
	//int _subdivisions = 0;


};

