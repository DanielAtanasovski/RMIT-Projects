#include "Player.h"
#include "../manager/Input.h"
#include "../math/Math.h"
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

Player::Player(Game& game, Vector2 position, float rotation) : game(game), CollidableEntity(position, rotation)
{
	// Determined by the largest side of the ship
	collisionRadius = Math::maxValue(abs(DRAW_TOP_POINT.y), abs(DRAW_RIGHT_POINT.x));

	Vector2 trailPosition = Vector2(position.x + direction.x, position.y + direction.y);
	trailEffect = new TrailEffect(trailPosition, TRAIL_COLOUR);
}

void Player::draw()
{
	glPushMatrix();

	// Apply Rotation and position
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

	glLineWidth(1.5f);
	// Outline Shape 
	glColor3f(OUTLINE_COLOUR.x, OUTLINE_COLOUR.y, OUTLINE_COLOUR.z);
	// Left Half
	glBegin(GL_LINE_LOOP);
	glVertex3f(DRAW_LEFT_POINT.x, DRAW_LEFT_POINT.y, 0);
	glVertex3f(DRAW_TOP_POINT.x, DRAW_TOP_POINT.y, 0);
	glVertex3f(DRAW_MID_POINT.x, DRAW_MID_POINT.y, 0);
	glEnd();

	// Right haf
	glBegin(GL_LINE_LOOP);
	glVertex3f(DRAW_RIGHT_POINT.x, DRAW_RIGHT_POINT.y, 0);
	glVertex3f(DRAW_TOP_POINT.x, DRAW_TOP_POINT.y, 0);
	glVertex3f(DRAW_MID_POINT.x, DRAW_MID_POINT.y, 0);
	glEnd();

	// Fill Shape
	glColor3f(FILL_COLOUR.x, FILL_COLOUR.y, FILL_COLOUR.z);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(DRAW_LEFT_POINT.x, DRAW_LEFT_POINT.y, 0);
	glVertex3f(DRAW_TOP_POINT.x, DRAW_TOP_POINT.y, 0);
	glVertex3f(DRAW_MID_POINT.x, DRAW_MID_POINT.y, 0);
	glVertex3f(DRAW_RIGHT_POINT.x, DRAW_RIGHT_POINT.y, 0);
	glEnd();

	// Draw Bounding Circle
	//CollidableEntity::drawDebugCollisionCircle();
	

	glPopMatrix();

	trailEffect->draw();
}

void Player::update(float deltaTime) {
	getInput();
	move(deltaTime);

	// Fire Rate
	if (!canShoot) {
		currentFireRate += deltaTime;
		if (currentFireRate >= FIRE_RATE) {
			canShoot = true;
			currentFireRate = 0;
		}	
	}

	// Trail
	if (isMoving)
		trailEffect->start();
	else
		trailEffect->stop();

	Vector2 trailPosition = Vector2(position.x + (direction.x * -5), position.y + (direction.y * -5));
	trailEffect->updateState(trailPosition, -direction.normalised());
	trailEffect->update(deltaTime);
}

void Player::move(float deltaTime)
{
	// Velocity
	velocity = inputVector.y * MOVE_SPEED * deltaTime;
	// Rotate
	rotation += inputVector.x * ROTATE_SPEED * deltaTime;

	direction.x = sinf(Math::degToRad(rotation));
	direction.y = cosf(Math::degToRad(rotation));

	// Clamp values
	Math::clamp(velocity, 0, MOVE_SPEED);

	if (rotation > 360)
		rotation = 0;
	else if (rotation < 0)
		rotation = 360;

	// Update Position
	position.x += sinf(Math::degToRad(rotation)) * velocity;
	position.y += cosf(Math::degToRad(rotation)) * velocity;

	// Request Redraw
	glutPostRedisplay();
}

void Player::shoot()
{
	if (canShoot) {
		canShoot = false;
		Vector2 spawnPoint = Vector2(position.x + direction.x * 5, position.y + direction.y * 5);
		Bullet* bullet = new Bullet(game, spawnPoint, direction);
		game.createCollidableEntity(bullet);
	}
}

void Player::getInput()
{
	inputVector.zero();
	if (Input::onPressed(KEY_UP)) {
		inputVector.y += 1;
	}

	if (Input::onPressed(KEY_LEFT)) {
		inputVector.x -= 1;
	}

	if (Input::onPressed(KEY_RIGHT)) {
		inputVector.x += 1;
	}

	if (Input::onPressed(KEY_SHOOT_1) || Input::onMouseLeftDown()) {
		shoot();
	}

	if (inputVector.magnitude() > 0)
		isMoving = true;
	else
		isMoving = false;
}
