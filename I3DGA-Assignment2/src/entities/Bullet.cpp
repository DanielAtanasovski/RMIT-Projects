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
	if (isDead)
		return;

	position.x += direction.x * SPEED * deltaTime;
	position.y += direction.y * SPEED * deltaTime;
	position.z += direction.z * SPEED * deltaTime;

	if (position.distanceTo(Vector3(0, 0, 0)) >= 300)
		this->isDead = true;
}

void Bullet::draw()
{
	if (isDead)
		return;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);

	glutSolidSphere(1, 10, 10);

	glPopMatrix();
}

void Bullet::onCollide(CollidableEntity& other)
{
	if (other.getTag() == "Asteroid") {
		isDead = true;
	}
}
