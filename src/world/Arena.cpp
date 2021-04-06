#include "Arena.h"
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

Arena::Arena(Player* player)
{
	this->player = player;
}

Arena::~Arena()
{
}

void Arena::draw()
{
	//glPointSize(10);
	glBegin(GL_LINES);
	glColor3f(topLineColour.x, topLineColour.y, topLineColour.z);
	glVertex3f(TOP_LEFT_POINT.x, TOP_LEFT_POINT.y, 0);
	glVertex3f(TOP_RIGHT_POINT.x, TOP_RIGHT_POINT.y, 0);

	glColor3f(rightLineColour.x, rightLineColour.y, rightLineColour.z);
	glVertex3f(TOP_RIGHT_POINT.x, TOP_RIGHT_POINT.y, 0);
	glVertex3f(BOTTOM_RIGHT_POINT.x, BOTTOM_RIGHT_POINT.y, 0);

	glColor3f(bottomLineColour.x, bottomLineColour.y, bottomLineColour.z);
	glVertex3f(BOTTOM_RIGHT_POINT.x, BOTTOM_RIGHT_POINT.y, 0);
	glVertex3f(BOTTOM_LEFT_POINT.x, BOTTOM_LEFT_POINT.y, 0);

	glColor3f(leftLineColour.x, leftLineColour.y, leftLineColour.z);
	glVertex3f(BOTTOM_LEFT_POINT.x, BOTTOM_LEFT_POINT.y, 0);
	glVertex3f(TOP_LEFT_POINT.x, TOP_LEFT_POINT.y, 0);
	glEnd();
}

void Arena::update()
{
	lineCheck();
}

void Arena::lineCheck()
{
	Vector2 playerPosition = player->getPosition();
	// Right Line
	if (TOP_RIGHT_POINT.x - playerPosition.x <= WARNING_DISTANCE)
		rightLineColour = WARNING_LINE_COLOUR;
	else
		rightLineColour = DEFAULT_LINE_COLOUR;
	// Left Line
	if (playerPosition.x - TOP_LEFT_POINT.x <= WARNING_DISTANCE)
		leftLineColour = WARNING_LINE_COLOUR;
	else
		leftLineColour = DEFAULT_LINE_COLOUR;

	// Top Line
	if (TOP_RIGHT_POINT.y - playerPosition.y <= WARNING_DISTANCE)
		topLineColour = WARNING_LINE_COLOUR;
	else
		topLineColour = DEFAULT_LINE_COLOUR;
	// Bottom Line
	if (playerPosition.y - BOTTOM_RIGHT_POINT.y <= WARNING_DISTANCE)
		bottomLineColour = WARNING_LINE_COLOUR;
	else
		bottomLineColour = DEFAULT_LINE_COLOUR;
}


