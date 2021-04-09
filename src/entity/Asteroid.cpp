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

Asteroid::Asteroid(Vector2 position, float rotation) : CollidableEntity(position, rotation) {
	collisionRadius = 10.0f;
	direction = Vector2(0, 0) - position;
}

void Asteroid::draw() {
	glPushMatrix();
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

	CollidableEntity::draw();
	glPopMatrix();
}

void Asteroid::update(float deltaTime) {
	
	direction = direction.normalised();
	position.x += direction.x * deltaTime * speed;
	position.y += direction.y * deltaTime * speed;
}