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

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	/* Put drawing code here */
	// ...

	/* Always check for errors! */
	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

/* You can ignore this for now, it just lets you exit when you press 'q' or ESC */
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	game = new Game();
	GlutCallbackInterface::getInstance().setGame(game);
}

void setupCallbacks() {
	glutDisplayFunc(GlutCallbackInterface::getInstance().displayCallback);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(GlutCallbackInterface::getInstance().displayReshapeCallback);

	glutMainLoop();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Tutorial 1");
	//glutFullScreen();
	
	init();
	setupCallbacks();

	return EXIT_SUCCESS;
}

#pragma region callbacks

#pragma endregion

