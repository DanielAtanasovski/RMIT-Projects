#pragma once
#include <vector>

#include "../../engine/scenes/Scene.h"
#include "../../engine/graphics/Light.h"
#include "../../engine/entities/Entity.h"
#include "../../engine/entities/CubeEntity.h"
#include "../entities/LightCube.h"
#include "../../engine/entities/Camera.h"
#include "../../engine/utilities/Input.h"
#include "../../engine/graphics/Renderer.h"
#include "../../engine/utilities/ResourceManager.h"
#include "../../engine/entities/SkyboxEntity.h"


class TestScene : public Scene{
public:
	TestScene(std::shared_ptr<Input> input, std::shared_ptr<Renderer> renderer);

	// Inherited via Scene
	virtual void Init(std::shared_ptr<ResourceManager> resourceManager) override;

	virtual void Update(float delta) override;

	virtual void Draw() override;

	virtual void Done() override;


private:

	// Entities
	std::unique_ptr<CubeEntity> _centerCube;
	std::unique_ptr<LightCube> _horizonalLightCube;
	std::unique_ptr<LightCube> _verticalLightCube;
	std::unique_ptr<SkyBoxEntity> _skyBox;

	// World
	std::unique_ptr<Camera> _camera;

	// Systems
	std::shared_ptr<Input> _input;
	std::shared_ptr<Renderer> _renderer;

	// Resources
	std::array<const char*, 6> _filePaths = {
		"./assets/textures/skybox/right.jpg",
		"./assets/textures/skybox/left.jpg",
		"./assets/textures/skybox/top.jpg",
		"./assets/textures/skybox/bottom.jpg",
		"./assets/textures/skybox/front.jpg",
		"./assets/textures/skybox/back.jpg"
	};

	void UpdateCamera(float delta);
	float _timeCount = 0.0f;
};