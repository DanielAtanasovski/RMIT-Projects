#include "Game.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <sstream>
#include <iomanip>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
	camera = new Camera(*this);
	player = new Player(*this, PLAYER_START_POSITION, PLAYER_START_ROTATION);
	arena = new Arena(*this);
	init();
}

void Game::init()
{
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light1);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction1);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light2);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_direction2);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_DEPTH_TEST);

	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

	if (FULLSCREEN)
		glutFullScreen();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	loadTextures();

	// Elapsed Time
	lastElapsedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
}

void Game::loadTextures()
{
	shipTexture = loadTexture("../resources/ship.png");
	std::cout << shipTexture << std::endl;
}

// Source: Tutorial 10
uint32_t Game::loadTexture(const char* filename)
{
	int width, height, components;
	unsigned char* data = stbi_load(filename, &width, &height, &components, STBI_rgb);

	unsigned int id;
	glPushAttrib(GL_TEXTURE_BIT);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);
	glPopAttrib();
	return id;
}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	//gluLookAt
	//(player->getPosition().x, player->getPosition().y + 3, player->getPosition().z - 10, // camera pos
	//	player->getForwardFocusPoint().x, player->getForwardFocusPoint().y, player->getForwardFocusPoint().z, // look at
	//	0, 1, 0); // up vector

	// main actors
	camera->draw();
	player->draw();
	arena->draw();

	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);

	/* Always check for errors! */
	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glFlush();
	glutSwapBuffers();
}

void Game::update() {
	// Calculate Delta Time
	float elapsed = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = elapsed - lastElapsedTime;
	
	camera->update(deltaTime);
	player->update(deltaTime);
	arena->update(deltaTime);

	checkCollidables();

	lastElapsedTime = elapsed;
}

void Game::onReshape(int width, int height)
{
	this->width = width;
	this->height = height;

	float aspect = (float)width / (float)height;
	// Set Viewport to window size
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, aspect, 1.0, 250.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Game::checkCollidables()
{
	std::vector<Asteroid*> asteroids = arena->getAsteroids();
	std::vector<Bullet*> bullets = player->getBullets();

	for (size_t i = 0; i < asteroids.size(); i++)
	{
		Asteroid currentAsteroid = *asteroids[i];
		for (size_t j = 0; j < bullets.size(); j++)
		{
			Bullet currentBullet = *bullets[j];

			if (currentBullet.getPosition().distanceTo(currentAsteroid.getPosition()) < 
				currentBullet.getCollisionRadius() + currentAsteroid.getCollisionRadius()) {

				currentBullet.onCollide(currentAsteroid);
				currentAsteroid.onCollide(currentBullet);
			}
		}
	}
}

bool Game::isPointSafe(Vector3 point, float radius)
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

	return false;
}

//void Game::CollisionCheckCollidables()
//{
//	std::vector<std::pair<int, int>> ignoreCollisionEvent = std::vector<std::pair<int, int>>();
//	// Loop all collidables (asteroids)
//	for (size_t i = 0; i < collidableEntities.size(); i++)
//	{
//		// Check with collision with player
//		CollidableEntity* c1 = collidableEntities[i];
//		Vector2 currentPosition = c1->getPosition();
//		float totalRadius = player->getCollisionRadius() + c1->getCollisionRadius();
//
//		if (!c1->isEnabled())
//			continue;
//
//		// Restart game on collision with player
//		if (c1->getTag() != "Bullet")
//			if (currentPosition.distanceTo(player->getPosition()) < totalRadius) {
//				player->setDead(true);
//				gameState = STATE_END;
//			}
//
//		if (isOutsideWorld(*c1))
//			queueCollidableDelete((int)i);
//
//		// Check for collisions Asteroid / Bullets->Arena
//		if (!c1->getInsideArena()) {
//			if (
//				((currentPosition.x + c1->getCollisionRadius()) < arena->TOP_RIGHT_POINT.x) &&
//				((currentPosition.x - c1->getCollisionRadius()) > arena->BOTTOM_LEFT_POINT.x) &&
//				((currentPosition.y + c1->getCollisionRadius()) < arena->TOP_RIGHT_POINT.y) &&
//				((currentPosition.y - c1->getCollisionRadius()) > arena->BOTTOM_LEFT_POINT.y)
//				)
//				c1->setInsideArena(true);
//		}
//		else {
//			// Walls
//			// right
//			if (currentPosition.distanceTo(Vector2(arena->BOTTOM_RIGHT_POINT.x, currentPosition.y)) < c1->getCollisionRadius()) {
//				c1->setVelocity(Vector2(-c1->getVelocity().x, c1->getVelocity().y));
//			}
//			// bottom
//			if (currentPosition.distanceTo(Vector2(currentPosition.x, arena->BOTTOM_RIGHT_POINT.y)) < c1->getCollisionRadius()){
//				c1->setVelocity(Vector2(c1->getVelocity().x, -c1->getVelocity().y));
//			}
//			// left
//			if (currentPosition.distanceTo(Vector2(arena->TOP_LEFT_POINT.x, currentPosition.y)) < c1->getCollisionRadius()) {
//				c1->setVelocity(Vector2(-c1->getVelocity().x, c1->getVelocity().y));
//			}
//			// top
//			if (currentPosition.distanceTo(Vector2(currentPosition.x, arena->TOP_LEFT_POINT.y)) < c1->getCollisionRadius()) {
//				c1->setVelocity(Vector2(c1->getVelocity().x, -c1->getVelocity().y));
//			}		
//		}
//
//		// Other Asteroids or Bullets
//		for (size_t j = 0; j < collidableEntities.size(); j++) {
//			// don't check collisions with self
//			if (j == i)
//				continue;
//
//			// Check if already calculated collision with this asteroid
//			if (Math::vectorContains(ignoreCollisionEvent, std::pair<int, int>((int)i, (int)j)))
//				continue;
//
//			CollidableEntity* c2 = collidableEntities[j];
//			Vector2 otherPosition = c2->getPosition();
//			totalRadius = c1->getCollisionRadius() + c2->getCollisionRadius();
//
//			if (!c2->isEnabled())
//				continue;
//
//			if (currentPosition.distanceTo(otherPosition) < totalRadius) {
//				// Collision
//				CollidableEntity copyOfC1 = CollidableEntity(*c1);
//				c1->onCollide(*c2);
//				c2->onCollide(copyOfC1);
//
//				// Add to list of resolved collisions
//				std::pair<int, int> collisionEvent = std::pair<int, int>((int)i, (int)j);
//				ignoreCollisionEvent.push_back(collisionEvent);
//			}
//		}
//	}
//}

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

void Game::killPlayer() {
	camera->reset();
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
