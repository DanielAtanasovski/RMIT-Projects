#include "Player.h"
#include <functional>


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

Player::Player(InputManager inputManager, float x, float y)
{
	inputManager.subscribeToKeyPress('w', std::bind(&Player::onMove, this, std::placeholders::_1));
	inputManager.subscribeToKeyPress('s', std::bind(&Player::onMove, this, std::placeholders::_1));
	inputManager.subscribeToKeyPress('a', std::bind(&Player::onMove, this, std::placeholders::_1));
	inputManager.subscribeToKeyPress('d', std::bind(&Player::onMove, this, std::placeholders::_1));
	this->x = x;
	this->y = y;
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::draw()
{
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
	glTranslatef(-x, -y, 0.0f);
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
	glVertex3f(x - 5, y - 10, 0);
	glVertex3f(x, y + 5, 0);
	glVertex3f(x, y - 5, 0);
	glVertex3f(x + 5, y - 10, 0);
	glEnd();
	glPopMatrix();
	glLoadIdentity();
}

void Player::onMove(char key)
{
	std::cout << "move! y: " << y << std::endl;
	switch (key)
	{
	case 'w':
		this->y += 1;
		break;
	case 's':
		this->y -= 1;
		break;
	case 'a':
		this->rotation -= 5;
		break;
	case 'd':
		this->rotation += 5;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
