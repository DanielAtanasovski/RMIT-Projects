// Daniel Atanasovski
#pragma once

#include "App.h"
#include "util/Input.h"
#include "Camera.h"
#include "drawing/Shapes.h"
#include <vector>
#include "drawing/HUD.h"
#include "scenes/Scene.h"

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
	Camera& getCamera() { return *_camera; }
private:
	bool _quitApp = false;
	
	void CheckInput();
	void CheckEvents();
	void Update(unsigned int td_milli);
	void Draw();

	// fps
	int _fps = 0;
	int _timeCount = 0;

	Camera *_camera = nullptr;
	HUD *_hud = nullptr;
	Input *_input = nullptr;

	std::array<Scene*, 6> _scenes;
	int _currentScene = 0;

	// Camera Controls 
	glm::vec3 _inputDirection = glm::vec3(0);
	float _cameraSpeed = 5.0f;
};

