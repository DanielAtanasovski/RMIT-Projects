// Daniel Atanasovski
// Based on Tony Saveski's ...
//-----------------------------------------------------------------------------
// RTRApp.h
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------

#pragma once

#include <glad/glad.h>
#include <sdl/SDL.h>

class App
{
public:
	App(const char* title, bool fullscreen = true, int width = 1024, int height = 768);
	virtual int Init();
	void Run();
	virtual void Done();
	// Default implementation of Tick
	virtual bool Tick(unsigned int td_milli) {
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
		glViewport(0, 0, _windowWidth, _windowHeight);

		// Swap Buffers
		SDL_GL_SwapWindow(_window);

		return quit;
	}

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

inline void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}