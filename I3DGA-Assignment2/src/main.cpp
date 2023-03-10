#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "GlutCallbackInterface.h"

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

Game* game;

void setupCallbacks() {
	glutDisplayFunc(GlutCallbackInterface::displayCallback);
	glutKeyboardFunc(GlutCallbackInterface::keyboardPressedCallback);
	glutKeyboardUpFunc(GlutCallbackInterface::keyboardReleasedCallback);
	glutMouseFunc(GlutCallbackInterface::mouseFuncCallback);
	glutPassiveMotionFunc(GlutCallbackInterface::mouseMotionCallback);
	glutMotionFunc(GlutCallbackInterface::mouseMotionCallback);
	glutReshapeFunc(GlutCallbackInterface::displayReshapeCallback);
	glutIdleFunc(GlutCallbackInterface::updateCallback);
}

void init()
{
	// Create game instance and setup callbacks
	game = new Game();
	GlutCallbackInterface::setGame(game);
	setupCallbacks();
}

int main(int argc, char** argv)
{
	// Setup GLUT and Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutCreateWindow("Asteroid Arena 3D");

	init();

	glutMainLoop();
	return EXIT_SUCCESS;
}

