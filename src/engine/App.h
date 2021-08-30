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