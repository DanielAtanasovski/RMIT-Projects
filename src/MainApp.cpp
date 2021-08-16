// Daniel Atanasovski

#include<iostream>
#include<glad/glad.h>
#include<glm/gtx/string_cast.hpp>
#include<glm/ext.hpp>
#include<sdl/SDL.h>
#include "MainApp.h"
#include "util/GLMUtil.h"

#include "drawing/Shapes.h"

int MainApp::Init() {
	if (int err = App::Init() != 0) {
		return err;
	}

	_camera = new Camera(_windowWidth, _windowHeight);
	_scenes[_currentScene]->Init();

	//if (_subdivisions == 0) {
	//	_mengerCubesArray.push_back(new Cube(glm::vec3(0, 0, 0), glm::vec3(5.0f)));
	//}
	//else {
	//	CalculateMengerSponge(glm::vec3(0, 0, 0), 5, _subdivisions-1);
	//}


	//Cube* cube = _mengerCubesArray[0];
	//std::cout << "- Cube 0 -" << std::endl;
	//std::cout << "Position: " <<glm::to_string(cube->getPosition()) << std::endl;
	//std::cout << "Size: " <<glm::to_string(cube->getSize()) << std::endl;
	//std::cout << "Potential: " << (int)cube->getPosition().x + (int)cube->getSize().x << std::endl << std::endl;

	//for (size_t i = 0; i < _mengerCubesArray.size(); i++)
	//{
	//	//std::cout << "- Cube " /*<< i << " -" << std::endl;
	//	//std::cout << "Position: " << glm::to_string(_mengerCubesArray[i]->getPosition()) << std::endl;
	//	//std::cout << "Size: " << glm::to_string(*/_mengerCubesArray[i]->getSize()) << std::endl;

	//	float diff = _mengerCubesArray[i]->getPosition().x - cube->getPosition().x;
	//	bool zPosMatch = _mengerCubesArray[i]->getPosition().z == cube->getPosition().z;
	//	bool yPosMatch = _mengerCubesArray[i]->getPosition().y == cube->getPosition().y;
	//	//std::cout << "diff: " << diff << std::endl;
	//	if ((diff >= cube->getSize().x && diff < cube->getSize().x * 2) && zPosMatch && yPosMatch) {
	//		//std::cout << "Found Cube to the Right" << std::endl;
	//	}
	//	else if ((int)_mengerCubesArray[i]->getPosition().x == (int)cube->getPosition().x - (int)cube->getSize().x) {
	//		//std::cout << "Found Cube to the Left" << std::endl;
	//	}
	//}

	return 0;
}

bool MainApp::Tick(unsigned int td_milli) {
	_quitApp = false;

	CheckInput();
	CheckEvents();
	Update(td_milli);
	Draw();

	return _quitApp;
}

void MainApp::DrawMengerSponge(glm::vec3 position, float size, int subdivisions)
{
	float offset = size / 3; // Interval for 3 cubes an Axis
	float halfOffset = offset / 2; // Center Points
	if (subdivisions > 0) {
		for (size_t zIndex = 0; zIndex < 3; zIndex++)
		{
			for (size_t yIndex = 0; yIndex < 3; yIndex++)
			{
				for (size_t xIndex = 0; xIndex < 3; xIndex++)
				{
					// Skip a couple of iterations for empty blocks
					if (((zIndex == 0 || zIndex == 2) && ((xIndex == 1 && yIndex == 1))) ||
						((zIndex == 1) && (yIndex == 1)) || // Middle Layer Row
						((zIndex == 1) && (yIndex == 0 || yIndex == 2) && (xIndex == 1))
						)
						continue;

					DrawMengerSponge(glm::vec3(
						position.x + ((xIndex * offset) - offset),
						position.y + ((yIndex * offset) - offset),
						position.z + ((zIndex * offset) - offset)),
						size / 3, subdivisions - 1);
				}
			}
		}
	}
	else {
		DrawOuterLayer(position.x - offset - halfOffset, position.x + offset + halfOffset, position.y + offset, position.z - offset - halfOffset, position.z + offset + halfOffset);
		DrawMiddleLayer(position.x - offset - halfOffset, position.x + offset + halfOffset, position.y, position.z - offset - halfOffset, position.z + offset + halfOffset);
		DrawOuterLayer(position.x - offset - halfOffset, position.x + offset + halfOffset, position.y - offset, position.z - offset - halfOffset, position.z + offset + halfOffset);
	}
}

void MainApp::DrawOuterLayer(float xMin, float xMax, float y, float zMin, float zMax)
{
	//std::cout << "DRAW" << std::endl << std::endl;
	// (length) / 3 cubes along x-axis = length of each cube
	// length of each cube / 2 = offset to use DrawCenteredCube
	float xInterval = ((xMax - xMin) / 3);
	float xOffset = xInterval / 2;
	float zInterval = ((zMax - zMin) / 3);
	float zOffset = zInterval / 2;
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			// if center
			if (row == 1 && col == 1)
				continue;

			//std::cout << "Row: " << row << ", Col: " << col << std::endl;
			//std::cout << "x: " << xMin + ((col * xInterval) + xOffset) << std::endl;
			//std::cout << "y: " << y << std::endl;
			//std::cout << "z: " << zMin + ((row * zInterval) + zOffset) << std::endl << std::endl;

			DrawCenteredCube(xMin + ((col * xInterval) + xOffset), y, zMin + ((row * zInterval) + zOffset), xInterval);
		}
	}
}

void MainApp::DrawMiddleLayer(float xMin, float xMax, float y, float zMin, float zMax) {
	float xInterval = ((xMax - xMin) / 3);
	float xOffset = xInterval / 2;
	float zInterval = ((zMax - zMin) / 3);
	float zOffset = zInterval / 2;

	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			// if center
			if (row == 0 && col == 1 ||
				row == 1 && col == 0 ||
				row == 1 && col == 1 ||
				row == 1 && col == 2 ||
				row == 2 && col == 1)
				continue;

			DrawCenteredCube(xMin + (col * xInterval + xOffset), y, zMin + (row * zInterval + zOffset), xInterval);
		}
	}
}

void MainApp::DrawCenteredCube(float x, float y, float z, float size) {
	float offset = size / 2;
	DrawCube(x - offset, y - offset, z + offset, x + offset, y + offset, z - offset);
}

void MainApp::DrawCube(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
	// Cube Vertices
	glm::vec3 vertices[] = {
		glm::vec3(minX, minY, minZ), // 0. Close Bottom Left
		glm::vec3(maxX, minY, minZ), // 1. Close Bottom Right
		glm::vec3(maxX, maxY, minZ), // 2. Close Top Right
		glm::vec3(minX, maxY, minZ), // 3. Close Top Left
		glm::vec3(minX, minY, maxZ), // 4. Far Bottom Left
		glm::vec3(maxX, minY, maxZ), // 5. Far Bottom Right
		glm::vec3(maxX, maxY, maxZ), // 6. Far Top Right
		glm::vec3(minX, maxY, maxZ)  // 7. Far Top Left
	};

	glBegin(GL_TRIANGLES);
	// Top
	glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);

	// Bottom
	glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);

	// Front
	glColor3f(0.0f, 1.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

	// Back
	glColor3f(0.0f, 1.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);

	// Left
	glColor3f(0.0f, 0.0f, 1.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);

	// Right
	glColor3f(0.0f, 0.0f, 1.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

	glColor3f(1.0f, 1.0f, 1.0f);


	glEnd();
}

void MainApp::CheckInput() {
	const Uint8* keys;
	_inputDirection = glm::vec3(0, 0, 0);
	SDL_PumpEvents();
	if (keys = SDL_GetKeyboardState(nullptr)) {
		if (keys[SDL_SCANCODE_ESCAPE]) {
			_quitApp = true;
		}
		if (keys[SDL_SCANCODE_A]) {
			_inputDirection.x = -1;
		}
		if (keys[SDL_SCANCODE_D]) {
			_inputDirection.x = 1;
		}
		if (keys[SDL_SCANCODE_W]) {
			_inputDirection.y = 1;
		}
		if (keys[SDL_SCANCODE_S]) {
			_inputDirection.y = -1;
		}
		if (keys[SDL_SCANCODE_Q]) {
			_inputDirection.z = -1;
		}
		if (keys[SDL_SCANCODE_E]) {
			_inputDirection.z = 1;
		}
		if (keys[SDL_SCANCODE_Z]) {
			_scenes[_currentScene]->ToggleDepthTest();
		}
		if (keys[SDL_SCANCODE_C]) {
			_scenes[_currentScene]->ToggleCullFaces();
		}

		if (keys[SDL_SCANCODE_EQUALS]) {
			_scenes[_currentScene]->SetSubdivisions(_scenes[_currentScene]->GetSubdivisions() + 1);
			_scenes[_currentScene]->Recalculate();
		}

		if (keys[SDL_SCANCODE_MINUS]) {
			_scenes[_currentScene]->SetSubdivisions(_scenes[_currentScene]->GetSubdivisions() - 1);
			_scenes[_currentScene]->Recalculate();
		}
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

