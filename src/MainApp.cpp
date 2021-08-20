// Daniel Atanasovski

#include <iostream>
#include <glad/glad.h>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>
#include <sdl/SDL.h>
#include "MainApp.h"
#include "util/GLMUtil.h"

#include "drawing/Shapes.h"

int MainApp::Init() {
	if (int err = App::Init() != 0) {
		return err;
	}

	_camera = new Camera(_windowWidth, _windowHeight);
	_scenes[_currentScene]->Init();
	return 0;
}

bool MainApp::Tick(unsigned int td_milli) {
	_quitApp = false;

	CheckEvents();
	CheckInput();
	Update(td_milli);
	Draw();

	return _quitApp;
}

void MainApp::CheckInput() {
	_inputDirection *= 0;
	_input.Update();

	// Quit
	if (_input.IsKeyReleased(SDL_SCANCODE_ESCAPE)) {
		_quitApp = true;
	}

	// Strafe 
	if (_input.IsKeyPressed(SDL_SCANCODE_A)) {
		_inputDirection.x = -1;
	}
	else if (_input.IsKeyPressed(SDL_SCANCODE_D)) {
		_inputDirection.x = 1;
	}

	// Vertical
	if (_input.IsKeyPressed(SDL_SCANCODE_S)) {
		_inputDirection.y = -1;
	}
	else if (_input.IsKeyPressed(SDL_SCANCODE_W)) {
		_inputDirection.y = 1;
	}

	// Zoom
	if (_input.IsKeyPressed(SDL_SCANCODE_Q)) {
		_inputDirection.z = -1;
	}
	else if (_input.IsKeyPressed(SDL_SCANCODE_E)) {
		_inputDirection.z = 1;
	}

	// Depth Test
	if (_input.IsKeyReleased(SDL_SCANCODE_Z)) {
		_scenes[_currentScene]->ToggleDepthTest();
	}

	// Culling
	if (_input.IsKeyReleased(SDL_SCANCODE_C)) {
		_scenes[_currentScene]->ToggleCullFaces();
	}

	// Subdivisions
	if (_input.IsKeyReleased(SDL_SCANCODE_EQUALS)) {
		_scenes[_currentScene]->SetSubdivisions(_scenes[_currentScene]->GetSubdivisions() + 1);
		_scenes[_currentScene]->Recalculate();
	} else if (_input.IsKeyReleased(SDL_SCANCODE_MINUS)) {
		_scenes[_currentScene]->SetSubdivisions(_scenes[_currentScene]->GetSubdivisions() - 1);
		_scenes[_currentScene]->Recalculate();
	}
}

void MainApp::CheckEvents()
{
	SDL_Event windowEvent;
	while (SDL_PollEvent(&windowEvent)) {
		if (windowEvent.type == SDL_QUIT) _quitApp = true;
	}
}

void MainApp::Update(unsigned int td_milli) {
	float step = td_milli / 1000.0f;
	_camera->UpdatePosition(_camera->GetPosition() + (_inputDirection * _cameraSpeed * step));
}

void MainApp::Draw() {
	glClearColor(0.0, 0.2, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, _windowWidth, _windowHeight);

	glBegin(GL_LINES);

	// X-AXIS
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);

	// Y-AXIS
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -10.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);

	// Z-AXIS
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);

	glEnd();

	_scenes[_currentScene]->Run();

	SDL_GL_SwapWindow(_window);
}

void MainApp::Done() {
	App::Done();
}

