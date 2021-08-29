#include "Scene5.h"
#include <glm/gtx/norm.hpp>

void Scene5::Init(HUD* hud, Camera* camera)
{
	SceneModern::Init(hud, camera);
	_camera->UpdatePosition(glm::vec3(0, 0, 35));
}

void Scene5::Recalculate()
{
	SceneModern::Recalculate();
	// Calculate biggest difference moved
	float largestDiff = 0.0f;
	float longestDistance = 0.0f;
	for (size_t i = 0; i < _verticesArray.size(); i++)
	{
		float distance = glm::length(_position - _verticesArray[i]);
		float diff = distance - (_size / 2);
		if (diff > largestDiff) {
			largestDiff = diff;
			longestDistance = distance;
		}		
	}
	
	// Modify verts
	for (size_t i = 0; i < _verticesArray.size(); i++)
	{		
		float factor = largestDiff / (_size / 2);
		float outsideSphere = glm::length(_position - _verticesArray[i]) - _size / 2;
		float subtractValue = factor * glm::length(_position - _verticesArray[i]);
		glm::vec3 direction = glm::normalize(_position - _verticesArray[i]);
		float newMagnitude = glm::length(_position - _verticesArray[i]) - subtractValue;
		glm::vec3 finalPos = direction * newMagnitude;
		//float differenceBetweenRadius = (_size / 2) - distance;
		//glm::vec3 direction = glm::normalize(_verticesArray[i] - _position);

		//float factor = distance / longestDistance;
		// Calculate new position = direction to move along + amount
		if (outsideSphere >= _size / 2) {
			_verticesArray[i] = (direction * (_size / 2));
		}
		else {
			_verticesArray[i] = finalPos;
		}
		
	}

	// Update Buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _verticesArray.size() * sizeof(glm::vec3), &_verticesArray.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Scene5::Update(unsigned int td_milli)
{
	float step = td_milli / 1000.0f;
}

void Scene5::Run()
{
	SceneModern::Run();
}

void Scene5::Done()
{
	SceneModern::Done();
}

void Scene5::SetupDraw()
{
	SceneModern::SetupDraw();
}

void Scene5::Draw()
{
	glBindVertexArray(_vertexArray);
	glDrawElements(GL_TRIANGLES, _faceIds.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Scene5::SetupBuffers()
{
	SceneModern::SetupBuffers();
}

void Scene5::SetupMaterials()
{
	SceneModern::SetupMaterials();
}

void Scene5::SetupLights()
{
	SceneModern::SetupLights();
}

