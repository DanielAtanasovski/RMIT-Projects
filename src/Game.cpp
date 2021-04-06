#include "Game.h"
#include <iostream>
#include <stdio.h>

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

Game::Game() {
	arena = new Arena();
	player = new Player(-70, -70);
	init();
}

Game::~Game() {

}

void Game::init()
{
	glMatrixMode(GL_PROJECTION);
	glOrtho(WORLD_UNIT_MIN, WORLD_UNIT_MAX, WORLD_UNIT_MIN, WORLD_UNIT_MAX, 0, WORLD_UNIT_DEPTH);
	glMatrixMode(GL_MODELVIEW);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

	if (FULLSCREEN)
		glutFullScreen();
}

void Game::draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	arena->draw();
	player->draw();

	/* Always check for errors! */
	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

void Game::update() {
	player->update();
}

void Game::onReshape(int width, int height)
{
	// Set Viewport to window size
	glViewport(0, 0, width, height);
	// Aspect Ration Calculation
	float aspect = (float)width / (float)height;
	std::cout << aspect << std::endl;

	// adjust projection to aspect ratio
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width >= height)
		glOrtho(WORLD_UNIT_MIN * aspect, WORLD_UNIT_MAX * aspect, WORLD_UNIT_MIN, WORLD_UNIT_MAX, 0.0, WORLD_UNIT_DEPTH);
	else
		glOrtho(WORLD_UNIT_MIN, WORLD_UNIT_MAX, WORLD_UNIT_MIN / aspect, WORLD_UNIT_MAX / aspect, 0.0, WORLD_UNIT_DEPTH);

	glMatrixMode(GL_MODELVIEW);


}
