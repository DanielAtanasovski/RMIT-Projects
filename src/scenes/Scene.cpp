#include "Scene.h"
#include <glad/glad.h>

void Scene::ToggleLighting()
{
	_lighting = !_lighting;

	if (_lighting)
		glDisable(GL_LIGHTING);
	else
		glEnable(GL_LIGHTING);
}

void Scene::ToggleCullFaces()
{
	_cullFaces = !_cullFaces;

	if (_cullFaces)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void Scene::ToggleDepthTest()
{
	_depthTest = !_depthTest;

	if (_depthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}
