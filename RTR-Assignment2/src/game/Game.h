#pragma once
#include <sdl/SDL_events.h>
#include <memory>

#include "../engine/graphics/shaders/Shader.h"
#include "../engine/entities/Camera.h"
#include "../engine/utilities/Input.h"
#include "../engine/entities/CubeEntity.h"

#include "entities/LightCube.h"
#include "../engine/scenes/Scene.h"
#include "../engine/graphics/Renderer.h"
#include "../engine/utilities/ResourceManager.h"

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

	std::shared_ptr<Input> _input;
	std::shared_ptr<Renderer> _renderer;
	std::shared_ptr<ResourceManager> _resourceManager;

	// Matrix
	glm::mat4 _perspectiveMatrix;

	// Screen
	float _width, _height;

	std::vector<std::unique_ptr<Scene>> _scenes;
	unsigned int _currentScene = 0;

	// Temporary
	//unsigned int VBO, VAO, EBO;
	//std::vector<glm::vec3> _vertices;
	//std::vector<unsigned int> _faces;
	//Shader _shader;
};

