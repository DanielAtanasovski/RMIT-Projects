#pragma once
// With help from
// https://www.falukdevelop.com/2016/08/18/simple-sdl-2-keyboard-key-status/

#include <sdl/SDL.h>
#include <glm/ext/vector_float2.hpp>

class Input {
public:
	void Init();

	void Update();

	bool IsKeyTriggered(const SDL_Scancode keyCode) const;

	bool IsKeyPressed(const SDL_Scancode keyCode) const;

	bool IsKeyReleased(const SDL_Scancode keyCode) const;

	void SetLastMouseMotion(float lastMotionX, float lastMotionY); 
	const glm::vec2& GetLastMouseMotion() const { return _lastMotion; };
private:
	Uint8 _previousInput[SDL_NUM_SCANCODES] = {};
	Uint8 _currentInput[SDL_NUM_SCANCODES] = {};
	glm::vec2 _lastMotion = glm::vec2(0);

};