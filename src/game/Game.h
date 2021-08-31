#pragma once
#include <sdl/SDL_events.h>
#include <memory>

#include "../engine/graphics/models/shapes/Shapes.h"
#include "../engine/graphics/Shader.h"
#include "../engine/entities/Camera.h"
#include "../engine/utilities/Input.h"

enum class GameState {
	GAME_ACTIVE,
	GAME_MENU,
};

class Game
{
public:
	Game();
	void Init(float width, float height, std::shared_ptr<Input> input);
	void Update(float delta);
	void OnEvent(SDL_Event event);
	void Render();

private:
	GameState _state;
	
	std::unique_ptr<Cube> _cube;
	std::unique_ptr<Camera> _camera;
	std::shared_ptr<Input> _input;

	// Matrix
	glm::mat4 _perspectiveMatrix;

	// Screen
	float _width, _height;

	// Temporary
	unsigned int VBO, VAO, EBO;
	std::vector<glm::vec3> _vertices;
	std::vector<unsigned int> _faces;
	Shader _shader;
};

