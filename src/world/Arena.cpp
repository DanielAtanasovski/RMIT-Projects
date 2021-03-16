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

Arena::Arena()
{
}

Arena::~Arena()
{
}

void Arena::draw()
{
	//glPointSize(10);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-WIDTH, -HEIGHT, 0);
	glVertex3f(-WIDTH, HEIGHT, 0);
	glVertex3f(WIDTH, HEIGHT, 0);
	glVertex3f(WIDTH, -HEIGHT, 0);
	glEnd();
}
