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


Asteroid::Asteroid(Game& game, Vector2 position, bool canSpawnAsteroid) : game(game), CollidableEntity(position, 0) {
	direction = (game.getPlayer().getPosition() - position).normalised();
	this->canSpawnAsteroid = canSpawnAsteroid;
	velocity = direction * SPEED;
	size = Math::getRandomFloat(MIN_SIZE, MAX_SIZE);
	collisionRadius = size;
	health = ceil(size / 4);
	generateAsteroid();
	tag = "Asteroid";
}

Asteroid::Asteroid(Game& game, Vector2 position, float size, bool canSpawnAsteroid) : game(game), CollidableEntity(position, 0) {
	this->size = size;
	this->canSpawnAsteroid = canSpawnAsteroid;
	// Set direction to player position
	direction = (game.getPlayer().getPosition() - position).normalised();
	velocity = Vector2(direction) * SPEED;
	collisionRadius = size;
	health = ceil(size / 4);
	generateAsteroid();
	tag = "Asteroid";
}

void Asteroid::draw() {
	if (!isDestroyed) {
		glPushMatrix();
		glTranslatef(position.x, position.y, 0.0f);
		glRotatef(rotation, 0.0f, 0.0f, -1.0f);

		/* Draw Health Value above Asteroid */
		Vector2 screenCoords = game.worldToScreenCoordinate(position);
		game.drawString(screenCoords.x, screenCoords.y, std::to_string((int)health));

		// Actual Asteroid
		drawAsteroid();

		glPopMatrix();
	}
	else {
		explosionEffect->draw();
	}
}

void Asteroid::setDirection(Vector2 direction) {
	this->direction = direction;
	this->velocity = direction * SPEED;
}

void Asteroid::generateAsteroid()
{
	for (size_t i = 0; i < MAX_POINTS; i++)
	{
		float radius = size + Math::getRandomFloat(MIN_SIZE_OFFSET, MAX_SIZE_OFFSET);

		float step = (float)i / MAX_POINTS * 2 * (float)M_PI;
		float x = radius * cosf(step);
		float y = radius * sinf(step);

		drawPoints.push_back(Vector2(x, y));
	}

}

void Asteroid::generateAsteroid(float size)
{
	for (size_t i = 0; i < MAX_POINTS; i++)
	{
		float radius = size + Math::getRandomFloat(size / 4, MAX_SIZE_OFFSET);
		float step = (float)i / MAX_POINTS * 2 * (float)M_PI;
		float x = radius * cosf(step);
		float y = radius * sinf(step);

		drawPoints.push_back(Vector2(x, y));
	}
}

void Asteroid::drawAsteroid() {

	glPushMatrix();

	//CollidableEntity::drawDebugCollisionCircle();

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
	if (!isDestroyed) {
		// Apply velocity
		position.x += velocity.x * deltaTime;
		position.y += velocity.y * deltaTime;

		// Rotate
		if (ROTATE_CLOCKWISE)
			rotation += ROTATION_SPEED * deltaTime;
		else
			rotation -= ROTATION_SPEED * deltaTime;
	}
	else {
		explosionEffect->update(deltaTime);
		if (explosionEffect->getDone()) {
			delete explosionEffect;
			game.deleteCollidableEntity(this);
		}
	}
}

void Asteroid::onCollide(CollidableEntity& other)
{
	// Collided with another asteroid
	if (other.getTag() == "Asteroid") {
		// Gather info
		Vector2 v1 = velocity;
		Vector2 v2 = other.getVelocity();
		// We'll use the radius to represent mass
		float m1 = collisionRadius;
		float m2 = other.getCollisionRadius();

		// Apply elastic collision formula
		Vector2 finalv1 = Vector2(
			(v1.x * (m1 - m2) + (2 * m2 * v2.x)) / (m1 + m2),
			(v1.y * (m1 - m2) + (2 * m2 * v2.y)) / (m1 + m2));

		// Apply velocity
		velocity = finalv1;
	}
	else if (other.getTag() == "Bullet") {
		// break
		health--;
		if (health <= 0 && !isDestroyed) {
			if (canSpawnAsteroid) {
				// Spawn Positions
				Vector2 perpDirection = Vector2(-direction.y, direction.x);
				Vector2 position1 = Vector2(position.x + (perpDirection.x * (size + 5)), position.y + (perpDirection.y * (size + 5)));
				Vector2 position2 = Vector2(position.x - (perpDirection.x * (size - 5)), position.y - (perpDirection.y * (size - 5)));

				// Create and set directions
				Asteroid* a1 = new Asteroid(game, position1, size / 2, false);
				float newDirx = cosf(Math::degToRad(45)) * direction.x - (sinf(Math::degToRad(45)) * direction.y);
				float newDiry = sinf(Math::degToRad(45)) * direction.x + (cosf(Math::degToRad(45)) * direction.y);
				a1->setDirection(Vector2(newDirx, newDiry));
				Asteroid* a2 = new Asteroid(game, position2, size / 2, false);
				newDirx = cosf(Math::degToRad(-45)) * direction.x - (sinf(Math::degToRad(-45)) * direction.y);
				newDiry = sinf(Math::degToRad(-45)) * direction.x + (cosf(Math::degToRad(-45)) * direction.y);
				a2->setDirection(Vector2(newDirx, newDiry));

				game.createCollidableEntity(a1);
				game.createCollidableEntity(a2);
			}

			isDestroyed = true;
			enabled = false;
			explosionEffect = new ExplosionEffect(position, Vector3(0.5f, 0.5f, 0.0f), 20);
			game.increaseScore(1);
		}

	}

}
