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

Player::Player(float x, float y)
{
	/*inputManager.subscribeToKeyPress('w', std::bind(&Player::onMove, this, std::placeholders::_1));
	inputManager.subscribeToKeyPress('s', std::bind(&Player::onMove, this, std::placeholders::_1));
	inputManager.subscribeToKeyPress('a', std::bind(&Player::onMove, this, std::placeholders::_1));
	inputManager.subscribeToKeyPress('d', std::bind(&Player::onMove, this, std::placeholders::_1));*/
	this->x = x;
	this->y = y;
}

Player::Player()
{
	this->x = 0;
	this->y = 0;
}

Player::~Player()
{
}

void Player::draw()
{
	// Apply Rotation
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
	//glTranslatef(-x, -y, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);

	// Outline
	//glBegin(GL_LINE_LOOP);
	//glVertex3f(10, 10, 0);
	//glVertex3f(15, 20, 0);
	//glVertex3f(15, 15, 0);
	//glVertex3f(20, 10, 0);
	//glVertex3f(15, 20, 0);
	//glEnd();

	// Fill
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(- 5, - 10, 0);
	glVertex3f(0, 5, 0);
	glVertex3f(0, - 5, 0);
	glVertex3f( 5, - 10, 0);
	glEnd();
	glPopMatrix();
	glLoadIdentity();
}

void Player::update() {
	getInput();
	move();
}

void Player::boundsCheck() {
	if (this->rotation > 360)
		this->rotation = 0;
	else if (this->rotation < 0)
		this->rotation = 360;

	if (velocity > 2)
		velocity = 2;
	else if (velocity < 0)
		velocity = 0;
}

void Player::move()
{
	// Move
	this->velocity += inputVector.y * MOVE_SPEED;
	// Rotate
	this->rotation += inputVector.x * ROTATE_SPEED;
	boundsCheck();

	// Update Position
	this->x += sinf(this->rotation * (M_PI / 180)) * this->velocity;
	this->y += cosf(this->rotation * (M_PI / 180)) * this->velocity;
	//std::cout << "rot: " << this->rotation << std::endl;

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
	//std::cout << "x: " << inputVector.x << std::endl;
}
