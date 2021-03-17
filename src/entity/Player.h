#pragma once

#include "../manager/InputManager.h"

class Player
{
public:
	Player(InputManager inputManager, float x, float y);
	Player();
	~Player();
	void draw();
	void idle();
	void onMove(char key);

private:
	float x, y, rotation = 0.0f;

};

