#pragma once

#include "Scene.h"
#include "../shaders/Shader.h"

class Scene2 : public Scene {
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

	// Inherited via Scene
	virtual void DrawMengerSponge() override;


	unsigned int _vertexBuffer, _materialIDBuffer, _vertexArray, _faceBuffer;
	Shader* _shader = nullptr;

	std::vector<unsigned int> _faceIds;
	// Ensuring that we arent binding arrays that havent been created yet
	bool firstRun = true; 
};