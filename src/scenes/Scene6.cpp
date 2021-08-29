#include "Scene6.h"

void Scene6::Init(HUD* hud, Camera* camera)
{
	SceneModern::Init(hud, camera);
	_camera->UpdatePosition(glm::vec3(0, 0, 35));
}

void Scene6::Recalculate()
{
	SceneModern::Recalculate();
}


void Scene6::Update(unsigned int td_milli)
{
	float step = td_milli / 1000.0f;

}

void Scene6::Run()
{
	SceneModern::Run();
}

void Scene6::Done()
{
	SceneModern::Done();
}

void Scene6::SetupDraw()
{
	SceneModern::SetupDraw();
}

void Scene6::Draw()
{
	glBindVertexArray(_vertexArray);
	glDrawElements(GL_TRIANGLES, _faceIds.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Scene6::setupBuffers()
{
	SceneModern::setupBuffers();
}

void Scene6::setupMaterials()
{
	SceneModern::setupMaterials();
}

void Scene6::SetupLights()
{
	SceneModern::SetupLights();
}

