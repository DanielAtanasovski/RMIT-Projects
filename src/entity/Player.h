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

#include <functional>
//#include "../manager/InputManager.h"
#include "../Game.h"

class Player
{
public:
	Player(Game* game);
	Player();
	~Player();
	void draw();
	void idle();
	void onMove(char key);

private:
	Game* game;
};

