#include "Scene.h"
#include <glad/glad.h>

void Scene::ToggleLighting()
{
	if (_lighting)
		glDisable(GL_LIGHTING);
	else
		glEnable(GL_LIGHTING);

	_lighting = !_lighting;
}

void Scene::ToggleCullFaces()
{
	if (_cullFaces)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	_cullFaces = !_cullFaces;
}

void Scene::ToggleDepthTest()
{
	if (_depthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	_depthTest = !_depthTest;
}
