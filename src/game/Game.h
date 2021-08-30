#pragma once
#include <sdl/SDL_events.h>

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
};

class Game
{
public:
	void Init();
	void Update(float delta);
	void OnEvent(SDL_Event event);
	void Render();

private:
	GameState _state;

};

