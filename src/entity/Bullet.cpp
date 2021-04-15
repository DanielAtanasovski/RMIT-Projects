#include "Bullet.h"
#include <iostream>

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

void Bullet::update(float deltaTime)
{
	position.x += direction.x * SPEED * deltaTime;
	position.y += direction.y * SPEED * deltaTime;
}

void Bullet::draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, 0.0f);
	glColor3f(colour.x, colour.y, colour.z);
	glPointSize(SIZE);

	glBegin(GL_POINTS);
	glVertex3f(0, 0, 0);
	glEnd();

	glPopMatrix();
}

void Bullet::onCollide(CollidableEntity& other)
{
	if (other.getTag() == "Asteroid") {
		game.deleteCollidableEntity(this);
	}
}
