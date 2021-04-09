#include "Arena.h"
#include <iostream>
#include "../Game.h"
#include "../entity/Asteroid.h"


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
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(topLineColour.x, topLineColour.y, topLineColour.z);
	glVertex3f(TOP_LEFT_POINT.x, TOP_LEFT_POINT.y, 0);
	glVertex3f(TOP_RIGHT_POINT.x, TOP_RIGHT_POINT.y, 0);

	glColor3f(rightLineColour.x, rightLineColour.y, rightLineColour.z);
	glVertex3f(TOP_RIGHT_POINT.x, TOP_RIGHT_POINT.y, 0);
	glVertex3f(BOTTOM_RIGHT_POINT.x, BOTTOM_RIGHT_POINT.y, 0);

	glColor3f(bottomLineColour.x, bottomLineColour.y, bottomLineColour.z);
	glVertex3f(BOTTOM_RIGHT_POINT.x, BOTTOM_RIGHT_POINT.y, 0);
	glVertex3f(BOTTOM_LEFT_POINT.x, BOTTOM_LEFT_POINT.y, 0);

	glColor3f(leftLineColour.x, leftLineColour.y, leftLineColour.z);
	glVertex3f(BOTTOM_LEFT_POINT.x, BOTTOM_LEFT_POINT.y, 0);
	glVertex3f(TOP_LEFT_POINT.x, TOP_LEFT_POINT.y, 0);
	glEnd();
}

void Arena::update(float deltaTime)
{
	lineCheck();
	spawnerUpdate(deltaTime);
}

void Arena::spawnAsteroid()
{
	int randInt = Math::getRandomInt(0, 360);
	float randomPoint = randInt / (float)360 * 2 * M_PI;
	float x = ASTEROID_SPAWN_RADIUS * cosf(randomPoint);
	float y = ASTEROID_SPAWN_RADIUS * sinf(randomPoint);


	std::cout << "Spawned Asteroid at " << x << ", " << y  << std::endl;
	Asteroid* newAsteroid = new Asteroid(Vector2(x, y), 0);
	game->createCollidableEntity(newAsteroid);
}

void Arena::spawnerUpdate(float deltaTime)
{
	currentSpawnTime += deltaTime;
	if (currentSpawnTime >= nextSpawnTime) {
		spawnAsteroid();
		currentSpawnTime = 0;
		nextSpawnTime = Math::getRandomFloat(MIN_SPAWN_TIME, MAX_SPAWN_TIME);
	}
}

void Arena::lineCheck()
{
	Vector2 playerPosition = player->getPosition();
	// Right Line
	if (TOP_RIGHT_POINT.x - playerPosition.x <= WARNING_DISTANCE)
		rightLineColour = WARNING_LINE_COLOUR;
	else
		rightLineColour = DEFAULT_LINE_COLOUR;
	// Left Line
	if (playerPosition.x - TOP_LEFT_POINT.x <= WARNING_DISTANCE)
		leftLineColour = WARNING_LINE_COLOUR;
	else
		leftLineColour = DEFAULT_LINE_COLOUR;

	// Top Line
	if (TOP_RIGHT_POINT.y - playerPosition.y <= WARNING_DISTANCE)
		topLineColour = WARNING_LINE_COLOUR;
	else
		topLineColour = DEFAULT_LINE_COLOUR;
	// Bottom Line
	if (playerPosition.y - BOTTOM_RIGHT_POINT.y <= WARNING_DISTANCE)
		bottomLineColour = WARNING_LINE_COLOUR;
	else
		bottomLineColour = DEFAULT_LINE_COLOUR;
}


