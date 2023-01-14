#pragma once
// With help from
// https://www.falukdevelop.com/2016/08/18/simple-sdl-2-keyboard-key-status/

#include <sdl/SDL.h>

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