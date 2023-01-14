#include "Arena.h"
#include <iostream>
#include "../Game.h"
#include "Asteroid.h"

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

void Arena::draw()
{
	drawArena();
	asteroidsDraw();
}

void Arena::update(float deltaTime)
{
	currentWaveTime += deltaTime;
	if (currentWaveTime >= TIME_BETWEEN_WAVES) {
		currentWaveTime = 0;
		if (asteroids.size() <= MAX_ASTEROIDS)
			spawnWave();
	}

	asteroidsUpdate(deltaTime);
	asteroidsCheck(deltaTime);
}

void Arena::drawArena() {

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(0.2f, 0.2f, 0.2f);

	glPushMatrix();

	if (playerCloseToWall(Vector3(0,0,1), (ARENA_SIZE / 2)))
		glColor3f(PLAYER_CLOSE_COLOR.x, PLAYER_CLOSE_COLOR.y, PLAYER_CLOSE_COLOR.z);
	else
		glColor3f(DEFAULT_COLOR.x, DEFAULT_COLOR.y, DEFAULT_COLOR.z);

	glTranslatef(0, 0, (ARENA_SIZE / 2));
	drawWallSegments(ARENA_SIZE);

	glPopMatrix();

	glPushMatrix();

	if (playerCloseToWall(Vector3(0, 0, 1), -(ARENA_SIZE / 2)))
		glColor3f(PLAYER_CLOSE_COLOR.x, PLAYER_CLOSE_COLOR.y, PLAYER_CLOSE_COLOR.z);
	else
		glColor3f(DEFAULT_COLOR.x, DEFAULT_COLOR.y, DEFAULT_COLOR.z);

	glTranslatef(0, 0, -(ARENA_SIZE / 2));
	drawWallSegments(ARENA_SIZE);


	glPopMatrix();

	// X Walls
	glPushMatrix();

	if (playerCloseToWall(Vector3(1, 0, 0), (ARENA_SIZE / 2)))
		glColor3f(PLAYER_CLOSE_COLOR.x, PLAYER_CLOSE_COLOR.y, PLAYER_CLOSE_COLOR.z);
	else
		glColor3f(DEFAULT_COLOR.x, DEFAULT_COLOR.y, DEFAULT_COLOR.z);

	glTranslatef((ARENA_SIZE / 2), 0, 0);
	glRotatef(90, 0, 1, 0);
	drawWallSegments(ARENA_SIZE);

	glPopMatrix();

	glPushMatrix();

	if (playerCloseToWall(Vector3(1, 0, 0), -(ARENA_SIZE / 2)))
		glColor3f(PLAYER_CLOSE_COLOR.x, PLAYER_CLOSE_COLOR.y, PLAYER_CLOSE_COLOR.z);
	else
		glColor3f(DEFAULT_COLOR.x, DEFAULT_COLOR.y, DEFAULT_COLOR.z);

	glTranslatef(-(ARENA_SIZE / 2), 0, 0);
	glRotatef(90, 0, 1, 0);
	drawWallSegments(ARENA_SIZE);
	glPopMatrix();

	// Y Walls
	glPushMatrix();

	if (playerCloseToWall(Vector3(0, 1, 0), (ARENA_SIZE / 2)))
		glColor3f(PLAYER_CLOSE_COLOR.x, PLAYER_CLOSE_COLOR.y, PLAYER_CLOSE_COLOR.z);
	else
		glColor3f(DEFAULT_COLOR.x, DEFAULT_COLOR.y, DEFAULT_COLOR.z);

	glTranslatef(0, (ARENA_SIZE / 2), 0);
	glRotatef(90, 1, 0, 0);
	drawWallSegments(ARENA_SIZE);
	glPopMatrix();

	glPushMatrix();

	if (playerCloseToWall(Vector3(0, 1, 0), -(ARENA_SIZE / 2)))
		glColor3f(PLAYER_CLOSE_COLOR.x, PLAYER_CLOSE_COLOR.y, PLAYER_CLOSE_COLOR.z);
	else
		glColor3f(DEFAULT_COLOR.x, DEFAULT_COLOR.y, DEFAULT_COLOR.z);

	glTranslatef(0, -(ARENA_SIZE/2), 0);
	glRotatef(90, 1, 0, 0);
	drawWallSegments(ARENA_SIZE);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glPopMatrix();


	//// Z Walls
	//glPushMatrix();
	//glDisable(GL_LIGHTING);

	//drawWall(X_DIRECTION);
	//drawWall(X_NEG_DIRECTION);
	//drawWall(Y_DIRECTION);
	//drawWall(Y_NEG_DIRECTION);
	//drawWall(Z_DIRECTION);
	//drawWall(Z_NEG_DIRECTION);

	//glEnable(GL_LIGHTING);
	//glPopMatrix();
	
}

//void Arena::drawWall(Vector3 direction)
//{
//	glPushMatrix();
//
//	if (playerCloseToWall(direction))
//		glColor3f(PLAYER_CLOSE_COLOR.x, PLAYER_CLOSE_COLOR.y, PLAYER_CLOSE_COLOR.z);
//	else
//		glColor3f(DEFAULT_COLOR.x, DEFAULT_COLOR.y, DEFAULT_COLOR.z);
//
//	glTranslatef(direction.x * (ARENA_SIZE / 2), direction.y * (ARENA_SIZE / 2), direction.z * (ARENA_SIZE / 2));
//	std::cout << direction.x * (ARENA_SIZE / 2) << " " << direction.y* (ARENA_SIZE / 2) << " " << direction.z* (ARENA_SIZE / 2) << std::endl;
//	//if (direction.z == 0)
//		//glRotatef(90, direction.x, direction.y, 0);
//	drawWallSegments(ARENA_SIZE);
//	//std::cout << direction << std::endl << std::endl;
//
//	glPopMatrix();
//}

void Arena::drawWallSegments(float size) {
	float startX, startY, endX, endY;
	startX = startY = -size / 2;
	endX = endY = size / 2;
	
	float stepInterval = size / 10;

	glBegin(GL_LINES);
	for (int i = 0; i <= 10; i++)
	{
		// Vertical
		glVertex3f(startX + (i * stepInterval), startY, 0);
		glVertex3f(startX + (i * stepInterval), endY, 0);

		// Horizontal
		glVertex3f(startX, startY + (i * stepInterval), 0);
		glVertex3f(endX, startY + (i * stepInterval), 0);
		
	}
	glEnd();
}

bool Arena::playerCloseToWall(Vector3 direction, float wallValue)
{
	bool ret = false;
	Vector3 playerRelevantAxisPositionVec = (game.getPlayer().getPosition() * direction);
	float playerRelevantAxisPosition = playerRelevantAxisPositionVec.x + playerRelevantAxisPositionVec.y + playerRelevantAxisPositionVec.z;

	if (abs(playerRelevantAxisPosition - wallValue) <= WARNING_DISTANCE)
		ret = true;
	
	// Check if player outside, if so, tell game
	if (abs(playerRelevantAxisPosition) > abs(wallValue))
		game.killPlayer();

	return ret;
}

void Arena::spawnAsteroid(Vector3 position, Vector3 direction)
{
	asteroids.push_back(new Asteroid(position, direction));
}

Vector3 Arena::getRandomAsteroidPosition()
{
	float randomX = Math::getRandomFloat(0, (float)1);
	float randomY = Math::getRandomFloat(0, (float)1);
	float randomZ = Math::getRandomFloat(0, (float)1);
	return Vector3(randomX, randomY, randomZ).normalised() * (ARENA_SIZE + ASTEROID_SPAWN_OFFSET);
}

void Arena::spawnWave()
{
	for (int i = 0; i < waveSize; i++)
	{
		Vector3 pos = getRandomAsteroidPosition();
		spawnAsteroid(pos, (game.getPlayer().getPosition() - pos).normalised());
	}
	waveSize++;
	waveSize = Math::clamp(waveSize, 0, MAX_WAVE_SIZE);
}

void Arena::asteroidsCheck(float deltaTime)
{
	// If out of world
	std::vector<Asteroid*>::iterator i = asteroids.begin();

	while (i != asteroids.end()) {
		if ((*i)->getDestroyed()) {
			i = asteroids.erase(i);
		}
		else {
			++i;
		}
	}
}

void Arena::asteroidsDraw()
{
	for (Asteroid* asteroid : asteroids) {
		asteroid->draw();
	}
}

void Arena::asteroidsUpdate(float deltaTime)
{
	for (Asteroid* asteroid : asteroids) {
		asteroid->update(deltaTime);
	}
}

