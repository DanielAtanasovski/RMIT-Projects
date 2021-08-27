// Daniel Atanasovski
#include <iostream>
#include <glad/glad.h>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>
#include <sdl/SDL.h>
#include "MainApp.h"
#include "util/GLMUtil.h"
#include "drawing/Shapes.h"
#include "scenes/Scene1.h"
#include "scenes/Scene2.h"
#include "scenes/Scene3.h"

int MainApp::Init() {
	if (int err = App::Init() != 0) {
		return err;
	}

	_scenes = { new Scene1(), new Scene2(), new Scene3() };
	_currentScene = 1; // Set to Modern Scene for renderdoc

	_input = new Input();
	_hud = new HUD();
	_hud->Init();
	_hud->SetDisplay(_windowWidth, _windowHeight, _refreshRate);
	_hud->SetScene(_currentScene + 1);

	_camera = new Camera(_windowWidth, _windowHeight);
	_scenes[_currentScene]->Init(_hud, _camera);
	_scenes[_currentScene]->Recalculate();
	return 0;
}

bool MainApp::Tick(unsigned int td_milli) {
	_quitApp = false;

	CheckEvents();
	CheckInput();
	Update(td_milli);
	Draw();

	_fps++;
	_timeCount += td_milli;
	if ((_timeCount / 1000) >= 1.0) {
		_timeCount = 0;
		_hud->SetFPS(_fps);
		_fps = 0;
	}

	return _quitApp;
}

void MainApp::CheckInput() {
	_inputDirection *= 0;
	_input->Update();

	// Quit
	if (_input->IsKeyReleased(SDL_SCANCODE_ESCAPE)) {
		_quitApp = true;
	}

	// Strafe 
	if (_input->IsKeyPressed(SDL_SCANCODE_A)) {
		_inputDirection.x = -1;
	}
	else if (_input->IsKeyPressed(SDL_SCANCODE_D)) {
		_inputDirection.x = 1;
	}

	// Vertical
	if (_input->IsKeyPressed(SDL_SCANCODE_E)) {
		_inputDirection.y = -1;
	}
	else if (_input->IsKeyPressed(SDL_SCANCODE_Q)) {
		_inputDirection.y = 1;
	}

	// Forward
	if (_input->IsKeyPressed(SDL_SCANCODE_S)) {
		_inputDirection.z = -1;
	}
	else if (_input->IsKeyPressed(SDL_SCANCODE_W)) {
		_inputDirection.z = 1;
	}

	// Depth Test
	if (_input->IsKeyReleased(SDL_SCANCODE_Z)) {
		_scenes[_currentScene]->ToggleDepthTest();
		_hud->SetDrawAttributes(_scenes[_currentScene]->isDepthTesting(),
			_scenes[_currentScene]->isLighting(), _scenes[_currentScene]->isCulling());
	}

	// Lighting
	if (_input->IsKeyReleased(SDL_SCANCODE_L)) {
		_scenes[_currentScene]->ToggleLighting();
		_hud->SetDrawAttributes(_scenes[_currentScene]->isDepthTesting(),
			_scenes[_currentScene]->isLighting(), _scenes[_currentScene]->isCulling());
	}

	// Culling
	if (_input->IsKeyReleased(SDL_SCANCODE_C)) {
		_scenes[_currentScene]->ToggleCullFaces();
		_hud->SetDrawAttributes(_scenes[_currentScene]->isDepthTesting(),
			_scenes[_currentScene]->isLighting(), _scenes[_currentScene]->isCulling());
	}

	// Subdivisions
	if (_input->IsKeyReleased(SDL_SCANCODE_EQUALS)) {
		_scenes[_currentScene]->SetSubdivisions(_scenes[_currentScene]->GetSubdivisions() + 1);
		_hud->SetSubdivisions(_scenes[_currentScene]->GetSubdivisions());
		_scenes[_currentScene]->Recalculate();
	}
	else if (_input->IsKeyReleased(SDL_SCANCODE_MINUS)) {
		if (_scenes[_currentScene]->GetSubdivisions() > 0) {
			_scenes[_currentScene]->SetSubdivisions(_scenes[_currentScene]->GetSubdivisions() - 1);
			_hud->SetSubdivisions(_scenes[_currentScene]->GetSubdivisions());
			_scenes[_currentScene]->Recalculate();
		}
	}

	// HUD
	if (_input->IsKeyReleased(SDL_SCANCODE_H)) {
		_hud->ToggleFullHUD();
	}

	// Scenes
	if (_input->IsKeyReleased(SDL_SCANCODE_1)) {
		_scenes[_currentScene]->Done();
		_currentScene = 0;
		_scenes[_currentScene]->Init(_hud, _camera);
		_hud->SetScene(_currentScene + 1);
	}
	else if (_input->IsKeyReleased(SDL_SCANCODE_2)) {
		_scenes[_currentScene]->Done();
		_currentScene = 1;
		_scenes[_currentScene]->Init(_hud, _camera);
		_hud->SetScene(_currentScene + 1);
	} else if (_input->IsKeyReleased(SDL_SCANCODE_3)) {
		_scenes[_currentScene]->Done();
		_currentScene = 2;
		_scenes[_currentScene]->Init(_hud, _camera);
		_hud->SetScene(_currentScene + 1);
	}
}

void MainApp::CheckEvents()
{
	SDL_Event windowEvent;
	while (SDL_PollEvent(&windowEvent)) {
		if (windowEvent.type == SDL_QUIT) _quitApp = true;
		if (windowEvent.type == SDL_MOUSEMOTION) {
			// Yaw & Pitch
			_camera->UpdateDirection(windowEvent.motion.xrel, windowEvent.motion.yrel);
		}
	}
}

void MainApp::Update(unsigned int td_milli) {
	float step = td_milli / 1000.0f;

	if (_inputDirection.x > 0)
		_camera->UpdatePosition(_camera->GetPosition() + (glm::normalize(glm::cross(_camera->GetFront(), _camera->GetUp())) * _cameraSpeed * step));
	else if (_inputDirection.x < 0)
		_camera->UpdatePosition(_camera->GetPosition() - (glm::normalize(glm::cross(_camera->GetFront(), _camera->GetUp())) * _cameraSpeed * step));

	if (_inputDirection.y > 0)
		_camera->UpdatePosition(_camera->GetPosition() + (_camera->GetUp() * _cameraSpeed * step));
	else if (_inputDirection.y < 0)
		_camera->UpdatePosition(_camera->GetPosition() - (_camera->GetUp() * _cameraSpeed * step));

	if (_inputDirection.z > 0)
		_camera->UpdatePosition(_camera->GetPosition() + (_camera->GetFront() * _cameraSpeed * step));
	else if (_inputDirection.z < 0)
		_camera->UpdatePosition(_camera->GetPosition() - (_camera->GetFront() * _cameraSpeed * step));
}

void MainApp::Draw() {
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_scenes[_currentScene]->Run();

	_hud->Draw();


	SDL_GL_SwapWindow(_window);
}

void MainApp::Done() {
	App::Done();
	delete _hud;
	delete _input;
	delete _camera;
}

