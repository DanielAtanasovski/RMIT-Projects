#pragma once

#include "SceneModern.h"
#include "../shaders/Shader.h"
#include "../drawing/Light.h"

class Scene4 : public SceneModern {
public:
	Scene4() {};

	// Inherited via Scene
	virtual void Init(HUD* hud, Camera* camera) override;
	virtual void Run() override;
	virtual void Done() override;
	virtual void Recalculate() override;
	virtual void Update(unsigned int td_milli) override;

private:
	void SetupBuffers();
	void SetupMaterials();
	void SetupLights();

	// Inherited via Scene
	virtual void SetupDraw() override;
	virtual void Draw() override;

	// Buffers
	unsigned int _instancedModelMatricesBuffer;

	std::array <glm::mat4, 9> _instanceModelMatrices = {
		// Top
		glm::mat4(1),
		glm::mat4(1),
		glm::mat4(1),
		// Middle
		glm::mat4(1),
		glm::mat4(1),
		glm::mat4(1),
		// Bottom
		glm::mat4(1),
		glm::mat4(1),
		glm::mat4(1)
	};

	const float _translationOffset = _size * 0.75f;
	const float _rotationSpeed = 10.0f;

	std::array<float, 9> _currentModelRotation = {
		// Top
		0,
		25,
		46,
		// Middle
		38,
		120,
		90,
		// Bottom
		220,
		160,
		10
	};

	std::array<glm::vec3, 9> _modelRotationDirection = {
		// Top
		glm::vec3(0, 0, 1),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 1),
		// Middle
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 1, 0),
		// Bottom
		glm::vec3(1, 1, 1),
		glm::vec3(0, 0, -1),
		glm::vec3(0, -1, 0)
	};

	// Starting from top... 3 x 3 transformations
	std::array<glm::vec3, 9> _modelTranslationValue = {
		// Top
		glm::vec3(-(_size + _translationOffset), (_size + _translationOffset), 0),
		glm::vec3(0, (_size + _translationOffset), 0),
		glm::vec3((_size + _translationOffset), (_size + _translationOffset), 0),
		// Middle
		glm::vec3(-(_size + _translationOffset), 0, 0),
		glm::vec3(0, 0, 0),
		glm::vec3((_size + _translationOffset), 0, 0),
		// Bottom
		glm::vec3(-(_size + _translationOffset), -(_size + _translationOffset), 0),
		glm::vec3(0, -(_size + _translationOffset), 0),
		glm::vec3((_size + _translationOffset), -(_size + _translationOffset), 0)
	};

};