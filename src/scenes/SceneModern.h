#pragma once

#include "Scene.h"
#include "../shaders/Shader.h"
#include "../drawing/Light.h"

class SceneModern : public Scene {
public:
	// Inherited via Scene
	virtual void Init(HUD* hud, Camera* camera) override;
	virtual void Run() override;
	virtual void Update(unsigned int td_milli) = 0;
	virtual void Done() override;
	virtual void Recalculate() override;

protected:
	void setupBuffers();
	void setupMaterials();

	// Inherited via Scene
	virtual void SetupDraw();
	virtual void Draw() override;

	unsigned int _vertexBuffer, _vertexArray, _faceBuffer;
	Shader* _shader = nullptr;

	std::vector<unsigned int> _faceIds;
	// Ensuring that we arent binding arrays that havent been created yet
	bool firstRun = true;

	// Inherited via Scene
	virtual void SetLightCount(int count) override;
	virtual void SetupLights() override;
};