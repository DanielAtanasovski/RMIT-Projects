// Daniel Atanasovski
#include "MainApp.h"

int MainApp::Init() {
	// Error Check
	if (int err = App::Init() != 0) {
		return err;
	}

	_game = std::make_unique<Game>();
	_game->Init();

	return 0;
}

bool MainApp::Tick(unsigned int td_milli) {
	_quitApp = false;

	CheckEvents();
	CheckInput();
	Update(td_milli);
	Draw();

	// FPS Count
	_fps++;
	_timeCount += td_milli;
	if ((_timeCount / (float)1000) >= 1.0) {
		_timeCount = 0;
		_fps = 0;
	}

	return _quitApp;
}

void MainApp::CheckInput() {
	_input->Update();
}

void MainApp::CheckEvents()
{
	SDL_Event windowEvent;
	while (SDL_PollEvent(&windowEvent)) {
		if (windowEvent.type == SDL_QUIT) _quitApp = true;
		_game->OnEvent(windowEvent);
	}
}

void MainApp::Update(unsigned int td_milli) {
	float step = td_milli / 1000.0f;
	_game->Update(step);
}

void MainApp::Draw() {
	glClearColor((GLfloat)0.1, (GLfloat)0.1, (GLfloat)0.6, (GLfloat)1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_game->Render();

	SDL_GL_SwapWindow(_window);
}

void MainApp::Done() {
	App::Done();
}

