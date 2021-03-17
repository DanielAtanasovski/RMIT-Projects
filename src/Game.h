#pragma once
#if _WIN32
#   include <Windows.h>
#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

#include "world/Arena.h"
#include "entity/Player.h"
//#include "manager/InputManager.h"
#include <iostream>
#include <stdio.h>

class Game
{
public:
	Game();
	~Game();
	void init();
	//void input(unsigned char key, int x, int y); // TODO: Move this to an input handler class
	void draw();
	void update();
	void onReshape(int width, int height);

	// References
	//InputManager getInputManager();

	// consts
	const bool FULLSCREEN = false;

private:
	Arena* arena = nullptr;
	Player* player = nullptr;
	//InputManager inputManager;

};

