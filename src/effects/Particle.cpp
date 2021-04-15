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
	this->colourStart = colour;
	this->colourCurrent = colour;
	this->speed = speed;
	this->maxLifetime = maxLifeTime;
	this->sizeStart = size;
	this->sizeCurrent = size;

	std::cout << colourCurrent.x << ", " << colourCurrent.y << ", " << colourCurrent.z << ", " << sizeEnd << std::endl;
}

Particle::Particle(Vector2 position, Vector2 direction, Vector3 colourStart, Vector3 colourEnd, float speed, float maxLifeTime, float size) {
	this->position = position;
	this->direction = direction;
	this->colourStart = colourStart;
	this->colourCurrent = colourStart;
	this->colourEnd = colourEnd;
	this->speed = speed;
	this->maxLifetime = maxLifeTime;
	this->sizeStart = size;
	this->sizeCurrent = size;
	
}

void Particle::draw()
{
	if (!done) {
		glPushMatrix();

		glTranslatef(position.x, position.y, 0.0f);
		glColor3f(colourCurrent.x, colourCurrent.y, colourCurrent.z);
		glPointSize(sizeCurrent);

		glBegin(GL_POINTS);
		glVertex3f(0, 0, 0);
		glEnd();

		glPopMatrix();
	}

}

void Particle::update(float deltaTime)
{
	currentLifetime += deltaTime;
	if (currentLifetime >= maxLifetime)
		done = true;	

	if (!done) {
		// Calculate Current Colour
		colourCurrent = Vector3::lerp(colourStart, colourEnd, (currentLifetime) / maxLifetime);
		// Calculate Current Size
		sizeCurrent = Math::lerp(sizeStart, sizeEnd, (currentLifetime) / maxLifetime);

		position.x += direction.x * speed * deltaTime;
		position.y += direction.y * speed * deltaTime;
	}
}
