#include "Scene3.h"

void Scene3::setupBuffers()
{
	SceneModern::setupBuffers();
}

void Scene3::setupMaterials()
{
	SceneModern::setupMaterials();
}

void Scene3::setupLights()
{
	SceneModern::setupLights();
}

void Scene3::SetupDraw()
{
	SceneModern::SetupDraw();
}

void Scene3::Draw()
{
	glm::mat4 modelMatrix = glm::mat4(1);
	for (int i = 0; i < 3; i++) {
		_shader->setMatrix4("modelMatrix", modelMatrix);
		glBindVertexArray(_vertexArray);
		glDrawElements(GL_TRIANGLES, _faceIds.size(), GL_UNSIGNED_INT, 0);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(_size, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0, 1, 0));
	}

	glBindVertexArray(0);
}

void Scene3::Recalculate()
{
	SceneModern::Recalculate();
}

void Scene3::Run()
{
	SceneModern::Run();
}

void Scene3::Done()
{
	SceneModern::Done();
}

void Scene3::Init(HUD* hud, Camera* camera)
{
	SceneModern::Init(hud, camera);
}





