#include "Player.h"
#include "../manager/Input.h"
#include "../math/Math.h"
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



//TODO: add inheritance from base GameObject class
Player::Player(Vector2 position, float rotation) : Entity(position, rotation)
{

}

//Player::Player()
//{
//	Entity::Entity();
//}

Player::~Player()
{
}

void Player::draw()
{
	glPushMatrix();

	// Apply Rotation and position
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

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

	glPopMatrix();
}

void Player::update(float deltaTime) {
	getInput();
	move(deltaTime);
}

void Player::move(float deltaTime)
{
	// Velocity
	velocity = inputVector.y * MOVE_SPEED * deltaTime;
	// Rotate
	rotation += inputVector.x * ROTATE_SPEED * deltaTime;

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

void Player::getInput()
{
	inputVector.zero();
	if (Input::onPressed(KEY_UP)) {
		inputVector.y += 1;
	}

	if (Input::onPressed(KEY_DOWN)) {
		inputVector.y -= 1;
	}

	if (Input::onPressed(KEY_LEFT)) {
		inputVector.x -= 1;
	}

	if (Input::onPressed(KEY_RIGHT)) {
		inputVector.x += 1;
	}
}
