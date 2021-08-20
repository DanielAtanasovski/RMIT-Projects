#pragma once
// With help from
// https://www.falukdevelop.com/2016/08/18/simple-sdl-2-keyboard-key-status/


#include <iostream>
#include <sdl/SDL.h>
#include "KeyState.h"
#include <unordered_map>
#include <array>
#include <iterator>

class Input {
public:
	void Init();

	void Update();

	bool IsKeyTriggered(const SDL_Scancode keyCode) const;

	bool IsKeyPressed(const SDL_Scancode keyCode) const;

	bool IsKeyReleased(const SDL_Scancode keyCode) const;

private:
	Uint8 _previousInput[SDL_NUM_SCANCODES];
	Uint8 _currentInput[SDL_NUM_SCANCODES];

};