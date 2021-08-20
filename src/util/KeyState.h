#pragma once

#include<sdl/SDL.h>

class KeyState {
public:
	KeyState(bool pressed = false, bool released = false) { _sdlPressed = pressed; _sdlReleased = released; };
	void setPressed(bool pressed) {
		_sdlPressed = pressed;
		_sdlPressed = false;
	};
	void setReleased(bool released) {
		_sdlReleased = released; 
		_sdlPressed = false;
	}
	bool getPressed() { return _sdlPressed; }
	bool getReleased() { return _sdlReleased; }
private:
	bool _sdlPressed = false;
	bool _sdlReleased = false;

};