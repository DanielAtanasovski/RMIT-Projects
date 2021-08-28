#pragma once

#include "SceneModern.h"
#include "../shaders/Shader.h"
#include "../drawing/Light.h"

class Scene2 : public SceneModern {
public:
	Scene2() {};

	// Inherited via Scene
	virtual void Init(HUD* hud, Camera* camera) override;
	virtual void Run() override;
	virtual void Done() override;
	virtual void Recalculate() override;
private:
	void setupBuffers();
	void setupMaterials();
	void setupLights();

	// Inherited via Scene
	virtual void SetupDraw() override;
	virtual void Draw() override;

};