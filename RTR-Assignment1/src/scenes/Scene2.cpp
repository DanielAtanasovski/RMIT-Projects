#include "Scene2.h"

void Scene2::SetupBuffers()
{
	SceneModern::SetupBuffers();
}

void Scene2::SetupMaterials()
{
	SceneModern::SetupMaterials();
}

void Scene2::SetupLights()
{
	SceneModern::SetupLights();
}

void Scene2::SetupDraw()
{
	SceneModern::SetupDraw();
}

void Scene2::Draw()
{
	SceneModern::Draw();
}

void Scene2::Update(unsigned int td_milli)
{
	_shader->use();
	_shader->setVec3("lights[0].Direction", _camera->GetFront());
	_shader->setVec3("lights[0].Position", _camera->GetPosition());
	_shader->setBool("lightingEnabled", _lighting);
	_shader->setBool("directionalEnabled", true);
	_shader->setInt("NumberOfLights", _numLights);
	glUseProgram(0);
}

void Scene2::Recalculate()
{
	SceneModern::Recalculate();
}

void Scene2::Run()
{
	SceneModern::Run();
}

void Scene2::Done()
{
	SceneModern::Done();
}

void Scene2::Init(HUD* hud, Camera* camera)
{
	SceneModern::Init(hud, camera);
}
