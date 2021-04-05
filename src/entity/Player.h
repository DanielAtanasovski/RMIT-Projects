#pragma once
#include "../math/Vector.h"

class Player
{
public:
	Player(float x, float y);
	Player();
	~Player();
	void draw();
	void update();

private:
	float x, y, rotation = 0.0f;
	void getInput();
	void move();
	void boundsCheck();
	Vector inputVector;
	float velocity = 0.0f;

	// Settings
	// TODO: Move to Game options class
	const char KEY_UP = 'W';
	const char KEY_DOWN = 'S';
	const char SHOOT = ' ';
	const char KEY_LEFT = 'A';
	const char KEY_RIGHT = 'D';
	const float ROTATE_SPEED = 5.0f;
	const float MOVE_SPEED = 2.0f;
};

