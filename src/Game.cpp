#include "Game.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <sstream>
#include <iomanip>

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
#include "manager/Input.h"

Game::Game() {
	player = new Player(*this, PLAYER_START_POSITION, PLAYER_START_ROTATION);
	arena = new Arena(*this);
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

	// state
	if (gameState == STATE_START) {
		drawString((width / 2) - (getStringSize(START_MESSAGE) / 2), (height / 2), START_MESSAGE);
	}
	else if (gameState == STATE_END) {
		drawString((width / 2) - (getStringSize(END_MESSAGE) / 2), (height / 2), END_MESSAGE);
	}
	
	// main actors
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

	// Draw UI
	std::stringstream stringStream;
	stringStream << "Time: " << std::fixed << std::setprecision(0) << floor(time);
	std::string timeString = stringStream.str();
	stringStream.str(std::string());
	stringStream << "Score: " << score;
	std::string scoreString = stringStream.str();

	drawString(abs((WORLD_UNIT_MAX + WORLD_UNIT_MIN) - (arena->WIDTH))/2, height - 50, timeString);
	drawString(width - (abs((WORLD_UNIT_MAX + WORLD_UNIT_MIN) - (arena->WIDTH)) / 2) - getStringSize(scoreString), height - 50, scoreString);


	glutSwapBuffers();
}

void Game::update() {
	// Calculate Delta Time
	float elapsed = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = elapsed - lastElapsedTime;
	

	if (gameState == STATE_START) {
		if (Input::onAnyKey()) {
			gameState = STATE_GAME;
		}
		lastElapsedTime = elapsed;
	}
	else if (gameState == STATE_END) {
		if (currentTimeout >= STATE_END_TIMEOUT) {
			if (Input::onAnyKey()) {
				restart();
			}
		}
		else {
			currentTimeout += deltaTime;
		}
		

		arena->update(deltaTime);
		// Loop Collidables
		for (size_t i = 0; i < collidableEntities.size(); i++)
		{
			collidableEntities[i]->update(deltaTime);
		}

		CollisionCheckCollidables();
		runQueueDelete();
		lastElapsedTime = elapsed;
	}
	else {
		time += deltaTime;
		player->update(deltaTime);
		arena->update(deltaTime);

		// Loop Collidables
		for (size_t i = 0; i < collidableEntities.size(); i++)
		{
			collidableEntities[i]->update(deltaTime);
		}

		// Check collisions
		if (playerOutOfBounds()) {
			gameState = STATE_END;
		}

		CollisionCheckCollidables();
		runQueueDelete();

		lastElapsedTime = elapsed;
	}

}

void Game::onReshape(int width, int height)
{
	this->width = width;
	this->height = height;
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
	asteroidsCount++;
}

void Game::deleteCollidableEntity(CollidableEntity* entity)
{
	std::vector<CollidableEntity*>::iterator found = std::find(collidableEntities.begin(), collidableEntities.end(), entity);
	if (found != collidableEntities.end()) {
		collidableEntities.erase(found);
	}
}

bool Game::isPointSafe(Vector2 point, float radius)
{
	for (size_t i = 0; i < collidableEntities.size(); i++)
	{
		float totalRadius = collidableEntities[i]->getCollisionRadius() + radius;
		if (point.distanceTo(collidableEntities[i]->getPosition()) < totalRadius) {
			std::cout << "Can't Spawn at " << point.x << "," << point.y << " because of " 
				<< collidableEntities[i]->getPosition().x << "," << collidableEntities[i]->getPosition().y<< std::endl;
			return false;
		}
			
	}
	return true;
}

void Game::restart()
{
	// Remove old instances
	collidableEntities.clear();
	
	// reset player
	player->setRotation(PLAYER_START_ROTATION);
	player->setPosition(PLAYER_START_POSITION);
	player->setDead(false);

	arena->restart();

	time = 0;
	score = 0;


	gameState = STATE_GAME;
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
		if (c1->getTag() != "Bullet")
			if (currentPosition.distanceTo(player->getPosition()) < totalRadius) {
				player->setDead(true);
				gameState = STATE_END;
			}

		if (isOutsideWorld(*c1))
			queueCollidableDelete((int)i);

		// Check for collisions Asteroid / Bullets->Arena
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
			// right
			if (currentPosition.distanceTo(Vector2(arena->BOTTOM_RIGHT_POINT.x, currentPosition.y)) < c1->getCollisionRadius()) {
				c1->setVelocity(Vector2(-c1->getVelocity().x, c1->getVelocity().y));
			}
			// bottom
			if (currentPosition.distanceTo(Vector2(currentPosition.x, arena->BOTTOM_RIGHT_POINT.y)) < c1->getCollisionRadius()){
				c1->setVelocity(Vector2(c1->getVelocity().x, -c1->getVelocity().y));
			}
			// left
			if (currentPosition.distanceTo(Vector2(arena->TOP_LEFT_POINT.x, currentPosition.y)) < c1->getCollisionRadius()) {
				c1->setVelocity(Vector2(-c1->getVelocity().x, c1->getVelocity().y));
			}
			// top
			if (currentPosition.distanceTo(Vector2(currentPosition.x, arena->TOP_LEFT_POINT.y)) < c1->getCollisionRadius()) {
				c1->setVelocity(Vector2(c1->getVelocity().x, -c1->getVelocity().y));
			}		
		}

		// Other Asteroids or Bullets
		for (size_t j = 0; j < collidableEntities.size(); j++) {
			// don't check collisions with self
			if (j == i)
				continue;

			// Check if already calculated collision with this asteroid
			if (Math::vectorContains(ignoreCollisionEvent, std::pair<int, int>((int)i, (int)j)))
				continue;

			CollidableEntity* c2 = collidableEntities[j];
			Vector2 otherPosition = c2->getPosition();
			totalRadius = c1->getCollisionRadius() + c2->getCollisionRadius();

			if (currentPosition.distanceTo(otherPosition) < totalRadius) {
				// Collision
				CollidableEntity copyOfC1 = CollidableEntity(*c1);
				c1->onCollide(*c2);
				c2->onCollide(copyOfC1);

				// Add to list of resolved collisions
				std::pair<int, int> collisionEvent = std::pair<int, int>((int)i, (int)j);
				ignoreCollisionEvent.push_back(collisionEvent);
			}
		}
	}
}

void Game::queueCollidableDelete(int index)
{
	queueDeleteList.push_back(index);
}

void Game::runQueueDelete()
{
	for(unsigned i = (int)queueDeleteList.size(); i-- > 0;)
	{
		collidableEntities.erase(collidableEntities.begin() + queueDeleteList[i]);
		asteroidsCount--;
	}

	queueDeleteList.clear();
}

bool Game::isOutsideWorld(CollidableEntity& entity)
{
	float totalRadius = entity.getCollisionRadius() + arena->ASTEROID_SPAWN_RADIUS;
	if (entity.getPosition().distanceTo(Vector2(0, 0)) > totalRadius)
		return true;

	return false;
}

Vector2 Game::worldToScreenCoordinate(Vector2 point) {
	float percentX = (((point.x - WORLD_UNIT_MIN) * 100) / (WORLD_UNIT_MAX - WORLD_UNIT_MIN)) / 100;
	float percentY = (((point.y - WORLD_UNIT_MIN) * 100) / (WORLD_UNIT_MAX - WORLD_UNIT_MIN)) / 100;
	
	float screenX = width * percentX;
	float screenY = height * percentY;


	return Vector2(screenX, screenY);
}

void Game::drawString(float x, float y, std::string str)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, width, 0.0, height, 0, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);
	float currentX = x;
	for (size_t i = 0; i < str.length(); i++)
	{
		glRasterPos2f(currentX, y);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		currentX += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
}

float Game::getStringSize(std::string str)
{
	float currentSize = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		currentSize += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
	return currentSize;
}
