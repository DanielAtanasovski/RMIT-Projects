#pragma once
#include "world/Arena.h"

class Game
{
public:
	Game();
	~Game();
	void draw();
	void update();
	void onReshape(int width, int height);

	// consts
	const bool FULLSCREEN = false;

private:
	Arena* arena = nullptr;

};

