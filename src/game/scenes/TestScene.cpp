#include "TestScene.h"

TestScene::TestScene(std::shared_ptr<Input> input) : _input(input)
{

}

void TestScene::Init()
{
	// Entities
	_camera = std::make_unique<Camera>();
	_centerCube = std::make_unique<CubeEntity>();
	_centerCube->SetShader(Shader("./assets/shaders/Standard.vert", "./assets/shaders/Standard.frag"));
	_centerCube->SetMaterial({
		glm::vec3(1.0f, 0.5f, 0.32f),
		glm::vec3(1.0f, 0.5f, 0.32f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		32.0f,
		glm::vec3(1),
		});
	_lightCube = std::make_unique<LightCube>(glm::vec3(10, 6, 10));

	// Transformations
	_camera->SetPosition(glm::vec3(0, 0, 10));
	_centerCube->SetScale(glm::vec3(5, 5, 5));

	// TODO: Move to Renderer
	// Set Perspective Matrix 
	_centerCube->SetPerspectiveMatrix(_perspectiveMatrix);
	_lightCube->SetPerspectiveMatrix(_perspectiveMatrix);

	// Add lights
	_pointLights.push_back(_lightCube->GetLight());

	// TODO: Add lights to Renderer
}

void TestScene::Update(float delta)
{
	UpdateCamera(delta);
	_centerCube->SetViewMatrix(_camera->GetViewMatrix());
	_lightCube->SetViewMatrix(_camera->GetViewMatrix());

	_timeCount += delta;
	_lightCube->SetPosition(glm::vec3(10 * glm::sin(_timeCount), 6 + glm::sin(_timeCount), 10 * glm::sin(_timeCount)));
}

void TestScene::Draw()
{
	// TODO: Update Renderer with Lights
	Shader& shader = _centerCube->GetShader();
	shader.use();
	shader.setVec3("light.Position", _pointLights[0]->Position);
	shader.setVec3("light.Ambient", _pointLights[0]->Ambient);
	shader.setVec3("light.Diffuse", _pointLights[0]->Diffuse);
	shader.setVec3("light.Specular", _pointLights[0]->Specular);
	shader.setVec3("viewPos", _camera->GetPosition());

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
