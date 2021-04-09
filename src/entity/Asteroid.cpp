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


Asteroid::Asteroid(Vector2 position, float rotation) : CollidableEntity(position, rotation) {
	collisionRadius = size;
	direction = Vector2(0, 0) - position;
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
	//glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.8f, 0.8f, 0.8f);
	
	for (size_t i = 0; i < MAX_POINTS; i++)
	{
		glVertex3f(drawPoints[i].x, drawPoints[i].y, 0);
	}
	glEnd();
	//glPopMatrix();
}

void Asteroid::update(float deltaTime) {
	
	direction = direction.normalised();
	position.x += direction.x * deltaTime * speed;
	position.y += direction.y * deltaTime * speed;

	if (rotateClockwise)
		rotation += rotationSpeed * deltaTime;
	else
		rotation -= rotationSpeed * deltaTime;
}