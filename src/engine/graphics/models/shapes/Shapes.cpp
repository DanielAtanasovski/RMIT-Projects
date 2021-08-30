#include "Shapes.h"


#include <glad/glad.h>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <glm/gtc/type_ptr.hpp>


Cube::Cube(glm::vec3 position, glm::vec3 size, std::vector<CubeFaces> disabledFaces) : _position(position), _size(size)
{
	_disabledFaces = disabledFaces;
	if (_disabledFaces.size() > 0)
		PruneFaces();
	else 
		_faces = std::vector<glm::ivec3>(_CUBE_INDICES.begin(), _CUBE_INDICES.end());

	// Transformations
	_vertices = std::vector<glm::vec3>(_CUBE_VERTICES, _CUBE_VERTICES + 8); // Size of array
	for (size_t i = 0; i < _vertices.size(); i++)
	{
		_vertices[i] *= _size;
		_vertices[i] += _position;
	}

	// Determine Materials
	for (size_t i = 0; i < _faces.size(); i++) {
		// Get Triangle Vertexes
		glm::ivec3 faceIndex = _faces[i];
		glm::vec3 pointA = _vertices[faceIndex.x];
		glm::vec3 pointB = _vertices[faceIndex.y];
		glm::vec3 pointC = _vertices[faceIndex.z];
	}
	

}

void Cube::draw() {
}

void Cube::PruneFaces()
{
	_faces = std::vector<glm::ivec3>(_CUBE_INDICES.begin(), _CUBE_INDICES.end());

	// Mark Removed Faces
	for (size_t i = 0; i < _disabledFaces.size(); i++)
	{
		switch (_disabledFaces[i]) {
		case CubeFaces::FRONT_FACE:
			_faces[0] = glm::ivec3(0, 0, 0);
			_faces[1] = glm::ivec3(0, 0, 0);
			break;
		case CubeFaces::BACK_FACE:
			_faces[2] = glm::ivec3(0, 0, 0);
			_faces[3] = glm::ivec3(0, 0, 0);
			break;
		case CubeFaces::LEFT_FACE:
			_faces[4] = glm::ivec3(0, 0, 0);
			_faces[5] = glm::ivec3(0, 0, 0);
			break;
		case CubeFaces::RIGHT_FACE:
			_faces[6] = glm::ivec3(0, 0, 0);
			_faces[7] = glm::ivec3(0, 0, 0);
			break;
		case CubeFaces::TOP_FACE:
			_faces[8] = glm::ivec3(0, 0, 0);
			_faces[9] = glm::ivec3(0, 0, 0);
			break;
		case CubeFaces::BOTTOM_FACE:
			_faces[10] = glm::ivec3(0, 0, 0);
			_faces[11] = glm::ivec3(0, 0, 0);
			break;
		}
	}

	// Remove Faces
	_faces.erase(std::remove_if(_faces.begin(), 
		_faces.end(),
		[](glm::ivec3 x) { return (x.x == 0 && x.y == 0 && x.z == 0); }),
		_faces.end());
}
