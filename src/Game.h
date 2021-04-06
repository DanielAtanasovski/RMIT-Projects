#pragma once

#include "world/Arena.h"
#include "entity/Player.h"
#include "manager/InputManager.h"

class Game
{
public:
	Game();
	~Game();
	void init();
	void input(unsigned char key, int x, int y); // TODO: Move this to an input handler class
	void draw();
	void update();
	void onReshape(int width, int height);
	// References
	InputManager getInputManager();
	// consts
	const bool FULLSCREEN = false;
	const float WORLD_UNIT_MIN = -100.0f;
	const float WORLD_UNIT_MAX = 100.0f;
	const float WORLD_UNIT_DEPTH = 1.0f;

private:
	Player* player = nullptr;
	Arena* arena = nullptr;
	InputManager inputManager;
};