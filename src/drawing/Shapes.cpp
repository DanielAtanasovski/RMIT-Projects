#include "Shapes.h"


#include <glad/glad.h>
#include <iostream>
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>


Cube::Cube(glm::vec3 position, glm::vec3 size, std::vector<CubeFaces> disabledFaces) : _position(position), _size(size)
{
	_disabledFaces = disabledFaces;
	if (_disabledFaces.size() > 0)
		calculateCurrentCubeIndices();
	else 
		_currentCubeIndices = std::vector<glm::ivec3>(_CUBE_INDICES.begin(), _CUBE_INDICES.end());

	// Transformations
	_currentCubeVertices = std::vector<glm::vec3>(_CUBE_VERTICES, _CUBE_VERTICES + 8);
	for (size_t i = 0; i < _currentCubeVertices.size(); i++)
	{
		_currentCubeVertices[i] *= _size;
		_currentCubeVertices[i] += _position;
	}

}

void Cube::draw() {
	glPushMatrix();
	// Draw Shape
	glBegin(GL_TRIANGLES);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	for (size_t i = 0; i < _currentCubeIndices.size(); i++)
	{
		// Get Triangle Vertexes
		glm::ivec3 faceIndex = _currentCubeIndices[i];
		glm::vec3 pointA = _currentCubeVertices[faceIndex.x];
		glm::vec3 pointB = _currentCubeVertices[faceIndex.y];
		glm::vec3 pointC = _currentCubeVertices[faceIndex.z];

		// Determine Colour
		if (pointA.x == pointB.x && pointA.x == pointC.x) {
			// Left / Right
			_newColour = _CUBE_COLOURS[0];
		}
		else if (pointA.y == pointB.y && pointA.y == pointC.y) {
			// Top / Bottom
			_newColour = _CUBE_COLOURS[1];
		}
		else if (pointA.z == pointB.z && pointA.z == pointC.z) {
			// Front / Back
			_newColour = _CUBE_COLOURS[2];
		}

		if (_newColour.r != _currentColour.r || _newColour.g != _currentColour.g || _newColour.b != _currentColour.b) {
			_currentColour = _newColour;
			glColor3f(_currentColour.r, _currentColour.g, _currentColour.b);
		}
			
		// Draw Vertex
		glVertex3f(
			pointA.x,
			pointA.y,
			pointA.z);
		glVertex3f(
			pointB.x,
			pointB.y,
			pointB.z);
		glVertex3f(
			pointC.x,
			pointC.y,
			pointC.z);
	}

	glEnd();
	glPopMatrix();
}

void Cube::calculateCurrentCubeIndices()
{
	_currentCubeIndices = std::vector<glm::ivec3>(_CUBE_INDICES.begin(), _CUBE_INDICES.end());

	// Mark Removed Faces
	for (size_t i = 0; i < _disabledFaces.size(); i++)
	{
		switch (_disabledFaces[i]) {
		case CubeFaces::FRONT_FACE:
			_currentCubeIndices[0] = glm::ivec3(0, 0, 0);
			_currentCubeIndices[1] = glm::ivec3(0, 0, 0);
			break;
		case CubeFaces::BACK_FACE:
			_currentCubeIndices[2] = glm::ivec3(0, 0, 0);
			_currentCubeIndices[3] = glm::ivec3(0, 0, 0);
			break;
		case CubeFaces::LEFT_FACE:
			_currentCubeIndices[4] = glm::ivec3(0, 0, 0);
			_currentCubeIndices[5] = glm::ivec3(0, 0, 0);
			break;
		case CubeFaces::RIGHT_FACE:
			_currentCubeIndices[6] = glm::ivec3(0, 0, 0);
			_currentCubeIndices[7] = glm::ivec3(0, 0, 0);
			break;
		case CubeFaces::TOP_FACE:
			_currentCubeIndices[8] = glm::ivec3(0, 0, 0);
			_currentCubeIndices[9] = glm::ivec3(0, 0, 0);
			break;
		case CubeFaces::BOTTOM_FACE:
			_currentCubeIndices[10] = glm::ivec3(0, 0, 0);
			_currentCubeIndices[11] = glm::ivec3(0, 0, 0);
			break;
		}
	}

	// Remove Faces
	_currentCubeIndices.erase(std::remove_if(_currentCubeIndices.begin(), 
		_currentCubeIndices.end(),
		[](glm::ivec3 x) { return (x.x == 0 && x.y == 0 && x.z == 0); }),
		_currentCubeIndices.end());
}
