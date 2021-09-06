#pragma once

#include <vector>
#include "../graphics/Light.h"
#include "../entities/Entity.h"

class Scene
{
public:
	// Scene
	Scene() { _entities = std::vector<Entity>(); _pointLights = std::vector<std::shared_ptr<PointLight>>(); };
	virtual void Init() = 0; // Initialise
	virtual void Update(float delta) = 0; // Use to update with delta
	virtual void Draw() = 0;
	virtual void Done() = 0; // Unbind stuff

	void SetPerspective(glm::mat4 perspectiveMatrix) { _perspectiveMatrix = perspectiveMatrix; };

protected:
	std::shared_ptr<DirectionalLight> _directionalLight;
	std::vector<std::shared_ptr<PointLight>> _pointLights;
	std::vector<Entity> _entities;

	// TODO:
	// TEMPORARY
	glm::mat4 _perspectiveMatrix;
};