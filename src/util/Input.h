#pragma once

#include <sdl/SDL.h>

class Input {
public:
	static void UpdateState();
	static bool GetKeyPressed(SDL_Scancode key) {};
	static bool GetKeyReleased(SDL_Scancode key) {};
private:

};