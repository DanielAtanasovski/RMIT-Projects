#include "Player.h"

Player::Player(Game* game)
{
	using namespace std::placeholders;
	game->getInputManager().subscribeToKeyPress('w', std::bind(&Player::onMove, this, std::placeholders::_1));
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::draw()
{
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
	glVertex3f(10, 10, 0);
	glVertex3f(15, 20, 0);
	glVertex3f(15, 12, 0);
	glVertex3f(20, 10, 0);
	glEnd();
}

void Player::onMove(char key)
{
	printf("w was pressed!");
}
