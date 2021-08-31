#include "Game.h"
#include <glad/glad.h>

Game::Game() : _shader("./assets/shaders/Standard.vert", "./assets/shaders/Standard.frag")
{
	_state = GameState::GAME_ACTIVE;
	_cube = std::make_unique<Cube>();

	_camera = std::make_unique<Camera>();

	_vertices = _cube->getVertices();
	_faces = _cube->getFaces();

	// Create Buffers
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Generate Vertex Arrays
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Load Vertex Data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices.front(), GL_STATIC_DRAW);

	// Load Indicies Data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _faces.size() * sizeof(unsigned int), &_faces.front(), GL_STATIC_DRAW);

	// Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::Init(float width, float height, std::shared_ptr<Input> input)
{
	_input = input;

	_perspectiveMatrix = glm::perspective(glm::radians<float>(45.0f), width / height, 0.1f, 1000.0f);
	
	_shader.use();
	_shader.setMatrix4("perspectiveMatrix", _perspectiveMatrix);
	_shader.setMatrix4("viewMatrix", _camera->GetViewMatrix());
	_shader.setMatrix4("modelMatrix", _cube->getModelMatrix());
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Game::Update(float delta)
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

	_camera->Move(_inputDirection, delta);
}

void Game::OnEvent(SDL_Event event)
{
	if (event.type == SDL_MOUSEMOTION) {
		_camera->SetDirection((float)event.motion.xrel, (float)event.motion.yrel);
	}
}

void Game::Render()
{
	_shader.use();
	_shader.setMatrix4("viewMatrix", _camera->GetViewMatrix());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (GLint)_faces.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

