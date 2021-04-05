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
	inputManager = InputManager();
	player = new Player(-70, -70);
}

Game::~Game() {

}

void Game::init()
{
	glMatrixMode(GL_PROJECTION);
	glOrtho(-100.0, 100.0, 0, 100.0, 0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

	if (FULLSCREEN)
		glutFullScreen();
}

void Game::input(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

void Game::draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	/* Put drawing code here */
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
		glOrtho(-100.0 * aspect, 100.0 * aspect, -100.0, 100.0, 0.0, 1.0);
	else
		glOrtho(-100.0, 100.0, -100.0 / aspect, 100.0 / aspect, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);


}

InputManager Game::getInputManager()
{
	return inputManager;
}
