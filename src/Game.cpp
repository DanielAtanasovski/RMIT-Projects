#include "Game.h"

Game::Game() {
	arena = new Arena();
	player = new Player(this);
	inputManager = InputManager();
}

Game::~Game() {

}

void Game::init()
{
	glMatrixMode(GL_PROJECTION);
	glOrtho(-100.0, 100.0, 0, 100.0, 0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	if (FULLSCREEN)
		glutFullScreen();
}

void Game::input(unsigned char key, int x, int y)
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

void Game::draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	/* Put drawing code here */
	arena->draw();
	player->draw();

	/* Always check for errors! */
	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

void Game::update() {

}

void Game::onReshape(int width, int height)
{
	// Set Viewport to window size
	glViewport(0, 0, width, height);
	// Aspect Ration Calculation
	float aspect = (float)width / (float)height;
	std::cout << aspect << std::endl;

	// adjust projection to aspect ratio
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width >= height)
		glOrtho(-100.0 * aspect, 100.0 * aspect, -100.0, 100.0, 0.0, 1.0);
	else
		glOrtho(-100.0, 100.0, -100.0 / aspect, 100.0 / aspect, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	
	
}

InputManager Game::getInputManager()
{
	return inputManager;
}
