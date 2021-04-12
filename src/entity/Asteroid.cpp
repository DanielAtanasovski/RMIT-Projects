#include "Asteroid.h"
#include <math.h>

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
#include <iostream>


Asteroid::Asteroid(Vector2 position, float rotation) : CollidableEntity(position, rotation) {
	collisionRadius = size;
	direction = (Vector2(0, 0) - position).normalised();
	velocity = Vector2(direction) * speed;
	generateAsteroid();
}

void Asteroid::draw() {
	glPushMatrix();
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

	CollidableEntity::draw();
	drawAsteroid();

	glPopMatrix();
}

void Asteroid::generateAsteroid()
{
	for (size_t i = 0; i < MAX_POINTS; i++)
	{
		float radius = size + Math::getRandomFloat(MIN_SIZE_OFFSET, MAX_SIZE_OFFSET);
		float step = (float)i / MAX_POINTS * 2 * M_PI;
		float x = radius * cosf(step);
		float y = radius * sinf(step);
		drawPoints.push_back(Vector2(x, y));
	}
	
}

void Asteroid::drawAsteroid() {
	glPushMatrix();

	CollidableEntity::drawDebugCollisionCircle();

	glBegin(GL_LINE_LOOP);
	glColor3f(OUTLINE_COLOUR.x, OUTLINE_COLOUR.y, OUTLINE_COLOUR.z);
	
	for (size_t i = 0; i < MAX_POINTS; i++)
	{
		glVertex3f(drawPoints[i].x, drawPoints[i].y, 0);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(FILL_COLOUR.x, FILL_COLOUR.y, FILL_COLOUR.z);

	for (size_t i = 0; i < MAX_POINTS; i++)
	{
		glVertex3f(drawPoints[i].x, drawPoints[i].y, 0);
	}
	glEnd();


	glPopMatrix();
}

void Asteroid::update(float deltaTime) {
	// Check if in arena


	// Apply velocity
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	// Rotate
	if (rotateClockwise)
		rotation += rotationSpeed * deltaTime;
	else
		rotation -= rotationSpeed * deltaTime;
}