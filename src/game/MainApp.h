// Daniel Atanasovski
#pragma once
#include "../engine/App.h"
#include <memory>
#include "Game.h"
#include "../engine/utilities/Input.h"

class MainApp : public App
{
public:
	MainApp(const char* title, bool fullscreen = false, int width = 1024, int height = 768)
		: App(title, fullscreen, width, height) {};
	int Init();
	void Done();
	bool Tick(unsigned int td_milli);

private:
	bool _quitApp = false;
	
	void CheckInput();
	void CheckEvents();
	void Update(unsigned int td_milli);
	void Draw();

	std::unique_ptr<Game> _game;
	std::unique_ptr<Input> _input;

	// fps
	int _fps = 0;
	int _timeCount = 0;

};

