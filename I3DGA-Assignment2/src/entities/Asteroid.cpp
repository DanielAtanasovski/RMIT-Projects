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


Asteroid::Asteroid(Vector3 position, Vector3 direction) : CollidableEntity(position, 0) {
	this->direction = direction;
	this->canSpawnAsteroid = canSpawnAsteroid;
	velocity = direction * SPEED;
	this->size = size;
	collisionRadius = size;
	health = ceil(size / 4);
	tag = "Asteroid";
}

void Asteroid::draw() {
	if (isDestroyed)
		return;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);

	glutSolidSphere(20, 10, 10);

	glPopMatrix();
}

void Asteroid::setDirection(Vector3 direction) {
	this->direction = direction;
	this->velocity = direction * SPEED;
}

void Asteroid::update(float deltaTime) {
	if (isDestroyed)
		return;

	position += velocity * deltaTime;

	if (position.distanceTo(Vector3(0, 0, 0)) >= 300)
		isDestroyed = true;
}

void Asteroid::onCollide(CollidableEntity& other)
{
	if (other.getTag() == "Bullet") {
		std::cout << "Should be destroyed!" << std::endl;
		isDestroyed = true;
	}
		
}
