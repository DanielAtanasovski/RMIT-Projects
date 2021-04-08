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
	player = new Player(Vector2(-70, -70), 45);
	arena = new Arena(player);
	init();
}

void Game::init()
{
	glMatrixMode(GL_PROJECTION);
	glOrtho(WORLD_UNIT_MIN, WORLD_UNIT_MAX, WORLD_UNIT_MIN, WORLD_UNIT_MAX, 0, WORLD_UNIT_DEPTH);
	glMatrixMode(GL_MODELVIEW);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

	if (FULLSCREEN)
		glutFullScreen();

	// Elapsed Time
	lastElapsedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
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
	// Calculate Delta Time
	float elapsed = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = elapsed - lastElapsedTime;

	player->update(deltaTime);
	arena->update();
	// Check collisions
	if (playerOutOfBounds()) {
		std::cout << "Player Out of Bounds!!!" << std::endl;
		restart();
	}
		


	lastElapsedTime = elapsed;
}

void Game::onReshape(int width, int height)
{
	// Set Viewport to window size
	glViewport(0, 0, width, height);
	// Aspect Ration Calculation
	float aspect = (float)width / (float)height;

	// adjust projection to aspect ratio
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width >= height)
		glOrtho(WORLD_UNIT_MIN * aspect, WORLD_UNIT_MAX * aspect, WORLD_UNIT_MIN, WORLD_UNIT_MAX, 0.0, WORLD_UNIT_DEPTH);
	else
		glOrtho(WORLD_UNIT_MIN, WORLD_UNIT_MAX, WORLD_UNIT_MIN / aspect, WORLD_UNIT_MAX / aspect, 0.0, WORLD_UNIT_DEPTH);

	glMatrixMode(GL_MODELVIEW);


}

void Game::restart()
{
	// Remove old instances
	// FIXME: Not efficient, should just reset them
	delete arena;
	delete player;

	player = new Player(Vector2(-70, -70), 45);
	arena = new Arena(player);
}

bool Game::playerOutOfBounds()
{
	Vector2 position = player->getPosition();
	float radius = player->getCollisionRadius();

	if (
		((position.x - radius) <= arena->TOP_LEFT_POINT.x) ||
		((position.y + radius) >= arena->TOP_LEFT_POINT.y) ||
		((position.x + radius) >= arena->BOTTOM_RIGHT_POINT.x) ||
		((position.y - radius) <= arena->BOTTOM_RIGHT_POINT.y)
		) {
		return true;
	}
	return false;
}
