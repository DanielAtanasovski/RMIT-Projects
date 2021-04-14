#include "Particle.h"

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

#include "../math/Math.h"
#include <iostream>

Particle::Particle(Vector2 position, Vector2 direction, Vector3 colour, float speed, float maxLifeTime, float size) {
	this->position = position;
	this->direction = direction;
	this->colour = colour;
	this->speed = speed;
	this->maxLifetime = maxLifeTime;
	this->size = size;
};

void Particle::draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, 0.0f);
	glColor3f(colour.x, colour.y, colour.z);

	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glVertex3f(0, 0, 0);
	glEnd();
	glPopMatrix();
}

void Particle::update(float deltaTime)
{
	currentLifetime += deltaTime;
	if (currentLifetime >= maxLifetime)
		done = true;

	//std::cout << direction.x << "," << direction.y << std::endl;
	//position += direction * speed * deltaTime;
	position.x += direction.x * speed * deltaTime;
	position.y += direction.y * speed * deltaTime;

	//std::cout << "pos: " << direction.x << direction.y << std::endl;
}
