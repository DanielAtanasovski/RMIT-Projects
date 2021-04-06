#include "Player.h"
#include "../manager/Input.h"


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
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

//TODO: add inheritance from base GameObject class
Player::Player(float x, float y)
{
	position = Vector2(x, y);
}

Player::Player()
{
	position = Vector2(0, 0);
}

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

void Player::update() {
	getInput();
	move();
}

void Player::boundsCheck() {
	if (rotation > 360)
		rotation = 0;
	else if (rotation < 0)
		rotation = 360;

	if (velocity > MOVE_SPEED)
		velocity = MOVE_SPEED;
	else if (velocity < 0)
		velocity = 0;
}

void Player::move()
{
	// Velocity
	velocity = inputVector.y * MOVE_SPEED;
	// Rotate
	rotation += inputVector.x * ROTATE_SPEED;
	boundsCheck();

	// Update Position
	// TODO: Move deg2Rad to math class
	position.x += sinf(rotation * (float(M_PI) / 180)) * velocity;
	position.y += cosf(rotation * (float(M_PI) / 180)) * velocity;

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
