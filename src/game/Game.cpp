#include "Game.h"
#include <glad/glad.h>
#include "scenes/TestScene.h"


Game::Game() : _shader("./assets/shaders/Standard.vert", "./assets/shaders/Standard.frag")
{

}

void Game::Init(float width, float height, std::shared_ptr<Input> input)
{
	_state = GameState::GAME_ACTIVE;

	_input = input;
	_scenes.push_back(std::make_unique<TestScene>(_input));

	_perspectiveMatrix = glm::perspective(glm::radians<float>(45.0f), width / height, 0.1f, 1000.0f);
	_scenes[_currentScene]->SetPerspective(_perspectiveMatrix);
	_scenes[_currentScene]->Init();

	// Wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Game::Update(float delta)
{
	_scenes[_currentScene]->Update(delta);
}

void Game::OnEvent(SDL_Event event)
{
}

void Game::Render()
{
	_scenes[_currentScene]->Draw();
}

