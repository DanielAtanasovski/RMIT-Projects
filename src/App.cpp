// Daniel Atanasovski
// Based on Tony Saveski's ...
//-----------------------------------------------------------------------------
// RTRApp.cpp
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------

#include<iostream>
#include<glad/glad.h>
#include<sdl/SDL.h>

#include "App.h"

App::App(const char* title, bool fullscreen, int width, int height) {
	_mainWindowTitle = title;
	_fullScreen = fullscreen;
	_windowWidth = width;
	_windowHeight = height;
	_screenWidth = 0;
	_screenHeight = 0;
	_window = nullptr;
	_renderer = nullptr;
	_context = nullptr;
}

int App::Init() {

	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "APP::SDL::ERROR: SDL2 video subsystem failed to init. ERROR: " 
			<< SDL_GetError() << std::endl;
		return -1;
	}

	// Render Doc
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	// Create Window
	if (_fullScreen) {
		_window = SDL_CreateWindow(
			_mainWindowTitle.c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			0, 0,
			SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	}
	else {
		_window = SDL_CreateWindow(
			_mainWindowTitle.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			_windowWidth, _windowHeight,
			SDL_WINDOW_OPENGL);
	}

	// Create Renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr) {
		std::cerr << "APP::SDL::RENDERER::ERROR: SDL2 Renderer couldn't be created. ERROR: " 
			<< SDL_GetError() << std::endl;
		return -2;
	}

	// Create OpenGL Context
	_context = SDL_GL_CreateContext(_window);
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cerr << "APP::SDL::CONTEXT::ERROR: SDL2 failed to create the OpenGL context." 
			<< std::endl;
		return -3;
	}

	// Set Display Settings
	SDL_DisplayMode displayMode;
	if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0) {
		_screenWidth = displayMode.w;
		_screenHeight = displayMode.h;
		if (_fullScreen) {
			_windowWidth = _screenWidth;
			_windowHeight = _screenHeight;
		}
		_refreshRate = displayMode.refresh_rate;
	}
	else {
		std::cerr << "APP::WARNING: SDL2 couldn't recieve current display mode information" 
			<< std::endl;
	}

	// Vsync
	SDL_GL_SetSwapInterval(_vsyncOn);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	// SDL Attributes
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	// Set OpenGL Defaults
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	std::cout << "APP::INFO: OpenGL Version: " << GLVersion.major << "." << GLVersion.minor 
		<< " Initialised." << std::endl;
	std::cout << "APP::INFO: Using GPU - " << glGetString(GL_VENDOR) << " " 
		<< glGetString(GL_RENDERER) << " -" << std::endl;

	return 0;
}

void App::Run() {
	bool quit = false;
	while (!quit)
	{
		static unsigned int last_time = 0;
		unsigned int cur_time = SDL_GetTicks();
		unsigned int td_milli = cur_time - last_time;
		last_time = cur_time;
		quit = Tick(td_milli);
	}
}

void App::Done() {
	SDL_GL_DeleteContext(_context);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();

	_window = nullptr;
	_renderer = nullptr;
	_context = nullptr;
}