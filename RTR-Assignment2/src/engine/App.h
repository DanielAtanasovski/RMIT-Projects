/// Daniel Atanasovski

#pragma once

#include <glad/glad.h>
#include <sdl/SDL.h>
#include <string>

class App
{
public:
	App(const char* title, bool fullscreen = true, int width = 1024, int height = 768);
	virtual int Init();
	void Run();
	virtual void Done();
	virtual bool Tick(unsigned int td_milli);

protected:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_GLContext _context;

	// Display
	std::string _mainWindowTitle;
	float _screenWidth;
	float _screenHeight;
	float _windowWidth;
	float _windowHeight;
	int _refreshRate;
	bool _fullScreen;
	bool _vsyncOn = false;
};