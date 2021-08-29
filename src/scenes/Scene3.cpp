#include "Scene3.h"

void Scene3::Init(HUD* hud, Camera* camera)
{
	SceneModern::Init(hud, camera);
	_camera->UpdatePosition(glm::vec3(0, 0, 80));
}

void Scene3::Recalculate()
{
	SceneModern::Recalculate();
}


void Scene3::Update(unsigned int td_milli)
{
	float step = td_milli / 1000.0f;
	for (size_t i = 0; i < 9; i++)
	{
		_currentModelRotation[i] += step * _rotationSpeed;
	}
}

void Scene3::Run()
{
	SceneModern::Run();
}

void Scene3::Done()
{
	SceneModern::Done();
}

void Scene3::SetupDraw()
{
	SceneModern::SetupDraw();
}

void Scene3::Draw()
{
	for (int i = 0; i < 9; i++) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, _modelTranslationValue[i]);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(_currentModelRotation[i]), _modelRotationDirection[i]);

		_shader->setMatrix4("modelMatrix", modelMatrix);
		glBindVertexArray(_vertexArray);
		glDrawElements(GL_TRIANGLES, _faceIds.size(), GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}

void Scene3::setupBuffers()
{
	SceneModern::setupBuffers();
}

void Scene3::setupMaterials()
{
	SceneModern::setupMaterials();
}

void Scene3::SetupLights()
{
	SceneModern::SetupLights();
}
