#pragma once
#include <vector>

#include "../../engine/scenes/Scene.h"
#include "../../engine/graphics/Light.h"
#include "../../engine/entities/Entity.h"
#include "../../engine/entities/CubeEntity.h"
#include "../entities/LightCube.h"
#include "../../engine/entities/Camera.h"
#include "../../engine/utilities/Input.h"


class TestScene : public Scene{
public:
	TestScene(std::shared_ptr<Input> input);

	// Inherited via Scene
	virtual void Init() override;

	virtual void Update(float delta) override;

	virtual void Draw() override;

	virtual void Done() override;


private:
	std::unique_ptr<CubeEntity> _centerCube;
	std::unique_ptr<LightCube> _lightCube;
	std::unique_ptr<Camera> _camera;
	std::shared_ptr<Input> _input;

	void UpdateCamera(float delta);
	float _timeCount = 0.0f;
};