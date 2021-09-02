#include "TestScene.h"

TestScene::TestScene(std::shared_ptr<Input> input) : _input(input)
{

}

void TestScene::Init()
{
	_camera = std::make_unique<Camera>();
	_centerCube = std::make_unique<CubeEntity>();
	_lightCube = std::make_unique<LightCube>(glm::vec3(0, 10, 0));

	_camera->SetPosition(glm::vec3(0, 0, 10));

	_centerCube->SetPerspectiveMatrix(_perspectiveMatrix);
	_lightCube->SetPerspectiveMatrix(_perspectiveMatrix);
}

void TestScene::Update(float delta)
{
	UpdateCamera(delta);
	_centerCube->SetViewMatrix(_camera->GetViewMatrix());
	_lightCube->SetViewMatrix(_camera->GetViewMatrix());
}

void TestScene::Draw()
{
	_centerCube->Draw();
	_lightCube->Draw();
}

void TestScene::Done()
{
}

void TestScene::UpdateCamera(float delta)
{
	glm::vec3 _inputDirection = glm::vec3(0);
	// Strafe 
	if (_input->IsKeyPressed(SDL_SCANCODE_A)) {
		_inputDirection.x = -1;
	}
	else if (_input->IsKeyPressed(SDL_SCANCODE_D)) {
		_inputDirection.x = 1;
	}

	// Vertical
	if (_input->IsKeyPressed(SDL_SCANCODE_E)) {
		_inputDirection.y = -1;
	}
	else if (_input->IsKeyPressed(SDL_SCANCODE_Q)) {
		_inputDirection.y = 1;
	}

	// Forward
	if (_input->IsKeyPressed(SDL_SCANCODE_S)) {
		_inputDirection.z = -1;
	}
	else if (_input->IsKeyPressed(SDL_SCANCODE_W)) {
		_inputDirection.z = 1;
	}

	_camera->SetDirection(_input->GetLastMouseMotion().x, _input->GetLastMouseMotion().y);
	_camera->Move(_inputDirection, delta);
}
