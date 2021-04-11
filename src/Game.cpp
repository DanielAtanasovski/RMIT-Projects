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
	arena = new Arena(player, this);
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

	// Loop Collidables
	for (size_t i = 0; i < collidableEntities.size(); i++)
	{
		collidableEntities[i]->draw();
	}

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
	arena->update(deltaTime);

	// Loop Collidables
	for (size_t i = 0; i < collidableEntities.size(); i++)
	{
		collidableEntities[i]->update(deltaTime);
	}

	// Check collisions
	if (playerOutOfBounds()) {
		std::cout << "Player Out of Bounds!" << std::endl;
		restart();
	}

	CollisionCheckCollidables();


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

void Game::createCollidableEntity(CollidableEntity* entity)
{
	collidableEntities.push_back(entity);
}

void Game::restart()
{
	// Remove old instances
	// FIXME: Not efficient, should just reset them
	delete arena;
	delete player;
	collidableEntities.clear();

	player = new Player(Vector2(-70, -70), 45);
	arena = new Arena(player, this);
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

void Game::CollisionCheckCollidables()
{
	for (size_t i = 0; i < collidableEntities.size(); i++)
	{
		// Check with collision with player
		Vector2 currentPosition = collidableEntities[i]->getPosition();
		float totalRadius = player->getCollisionRadius() + collidableEntities[i]->getCollisionRadius();

		if (currentPosition.distanceTo(player->getPosition()) < totalRadius) {
			restart();
		}

		// Other Asteroids
		for (size_t j = 0; j < collidableEntities.size(); j++) {
			// don't check collisions with self
			if (j == i)
				continue;

			Vector2 otherPosition = collidableEntities[j]->getPosition();
			totalRadius = collidableEntities[i]->getCollisionRadius() + collidableEntities[j]->getCollisionRadius();

			if (currentPosition.distanceTo(otherPosition) < totalRadius) {
				std::cout << "Collision Between Asteroids!" << std::endl;
			}

		}
	}
}
