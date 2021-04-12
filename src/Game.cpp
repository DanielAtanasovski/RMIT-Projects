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
	std::vector<std::pair<int, int>> ignoreCollisionEvent = std::vector<std::pair<int, int>>();
	// Loop all collidables (asteroids)
	for (size_t i = 0; i < collidableEntities.size(); i++)
	{
		// Check with collision with player
		CollidableEntity* c1 = collidableEntities[i];
		Vector2 currentPosition = c1->getPosition();
		float totalRadius = player->getCollisionRadius() + c1->getCollisionRadius();

		// Restart game on collision with player
		if (currentPosition.distanceTo(player->getPosition()) < totalRadius) {
			restart();
		}

		// Check if in arena
		if (!c1->getInsideArena()) {
			if (
				((currentPosition.x + c1->getCollisionRadius()) < arena->TOP_RIGHT_POINT.x) &&
				((currentPosition.x - c1->getCollisionRadius()) > arena->BOTTOM_LEFT_POINT.x) &&
				((currentPosition.y + c1->getCollisionRadius()) < arena->TOP_RIGHT_POINT.y) &&
				((currentPosition.y - c1->getCollisionRadius()) > arena->BOTTOM_LEFT_POINT.y)
				)
				c1->setInsideArena(true);
		}
		else {
			// Walls
			if (currentPosition.distanceTo(Vector2(arena->BOTTOM_RIGHT_POINT.x, currentPosition.y)) < c1->getCollisionRadius()) {
				c1->setVelocity(Vector2(-c1->getVelocity().x, c1->getVelocity().y));
			}
				
			if (currentPosition.distanceTo(Vector2(currentPosition.x, arena->BOTTOM_RIGHT_POINT.y)) < c1->getCollisionRadius()){
				c1->setVelocity(Vector2(c1->getVelocity().x, -c1->getVelocity().y));
			}
				
			if (currentPosition.distanceTo(Vector2(arena->TOP_LEFT_POINT.x, currentPosition.y)) < c1->getCollisionRadius()) {
				c1->setVelocity(Vector2(-c1->getVelocity().x, c1->getVelocity().y));
			}
			
			if (currentPosition.distanceTo(Vector2(currentPosition.x, arena->TOP_LEFT_POINT.y)) < c1->getCollisionRadius()) {
				c1->setVelocity(Vector2(c1->getVelocity().x, -c1->getVelocity().y));
			}
				
		}



		// Other Asteroids
		for (size_t j = 0; j < collidableEntities.size(); j++) {
			// don't check collisions with self
			if (j == i)
				continue;

			// Check if already calculated collision with this asteroid
			if (Math::vectorContains(ignoreCollisionEvent, std::pair<int, int>(i, j)))
				continue;

			CollidableEntity* c2 = collidableEntities[j];
			Vector2 otherPosition = c2->getPosition();
			totalRadius = c1->getCollisionRadius() + c2->getCollisionRadius();

			if (currentPosition.distanceTo(otherPosition) < totalRadius) {
				// Gather info
				Vector2 v1 = c1->getVelocity();
				Vector2 v2 = c2->getVelocity();
				// We'll use the radius to represent mass
				float m1 = c1->getCollisionRadius();
				float m2 = c2->getCollisionRadius();

				// Apply elastic collision formula
				Vector2 finalv1 = Vector2(
					(v1.x * (m1 - m2) + (2 * m2 * v2.x)) / (m1 + m2),
					(v1.y * (m1 - m2) + (2 * m2 * v2.y)) / (m1 + m2));
				Vector2 finalv2 = Vector2(
					(v2.x * (m2 - m1) + (2 * m1 * v1.x)) / (m1 + m2),
					(v2.y * (m2 - m1) + (2 * m1 * v1.y)) / (m1 + m2));

				// Apply velocity
				c1->setVelocity(finalv1);
				c2->setVelocity(finalv2);

				// Add to list of resolved collisions
				std::pair<int, int> collisionEvent = std::pair<int, int>(i, j);
				ignoreCollisionEvent.push_back(collisionEvent);
			}
		}
	}
}
