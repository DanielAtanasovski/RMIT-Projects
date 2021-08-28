#pragma once

#include "Scene.h"

class Scene1 : public Scene {
public:
	using Scene::Scene;

	void Init(HUD* hud, Camera* camera) override;
	void Run() override;
	void Done() override;
private:
	virtual void Draw() override;

	GLfloat _cameraLightPosition[4] = { 0, 0, 0, 0 };
	GLfloat _cameraLightDirection[3] = { 0, 0, 0 };
};