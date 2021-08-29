#pragma once

#include "Scene.h"

class Scene1 : public Scene {
public:
	using Scene::Scene;

	void Init(HUD* hud, Camera* camera) override;
	void Update(unsigned int td_milli) override;
	void Run() override;
	void Done() override;
private:
	virtual void Draw() override;
	void UpdateLights();

	// Inherited via Scene
	virtual void SetupLights() override;
	virtual void SetLightCount(int count) override;
};