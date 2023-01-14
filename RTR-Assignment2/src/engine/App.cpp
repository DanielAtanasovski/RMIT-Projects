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

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

App::App(const char* title, bool fullscreen, int width, int height) {
	_mainWindowTitle = title;
	_fullScreen = fullscreen;
	_windowWidth = (float)width;
	_windowHeight = (float)height;
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

	// SDL Attributes
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);


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
			(int)_windowWidth, (int)_windowHeight,
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
		_screenWidth = (float)displayMode.w;
		_screenHeight = (float)displayMode.h;
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

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugOutput, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

	// Set OpenGL Defaults
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	//glShadeModel(GL_SMOOTH);

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

bool App::Tick(unsigned int td_milli) {
	bool quit = false;
	SDL_Event windowEvent;

	std::cout << "App::Tick()" << std::endl;

	// Loop Through Events
	while (SDL_PollEvent(&windowEvent)) {
		if (windowEvent.type == SDL_QUIT) quit = true;
	}

	// Draw
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, (GLsizei)_windowWidth, (GLsizei)_windowHeight);

	// Swap Buffers
	SDL_GL_SwapWindow(_window);

	return quit;
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

