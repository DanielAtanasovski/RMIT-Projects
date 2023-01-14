#include "Shapes.h"


#include <glad/glad.h>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <glm/gtc/type_ptr.hpp>


//Cube::Cube(glm::vec3 position, glm::vec3 size, std::vector<CubeFaces> disabledFaces) : _position(position), _scale(size)
//{
//	std::vector<glm::ivec3> tempFaces = std::vector<glm::ivec3>();
//	_disabledFaces = disabledFaces;
//	if (_disabledFaces.size() > 0)
//		PruneFaces();
//	else 
//		tempFaces = std::vector<glm::ivec3>(_CUBE_INDICES.begin(), _CUBE_INDICES.end());
//
//	// Transformations
//	_vertices = std::vector<glm::vec3>(_CUBE_VERTICES, _CUBE_VERTICES + 8); // Size of array
//	
//	ConvertFaces(tempFaces);
//}
//
//void Cube::Draw() {
//}
//
//void Cube::PruneFaces()
//{
//	std::vector<glm::ivec3> tempFaces = std::vector<glm::ivec3>(_CUBE_INDICES.begin(), _CUBE_INDICES.end());
//
//	// Mark Removed Faces
//	for (size_t i = 0; i < _disabledFaces.size(); i++)
//	{
//		switch (_disabledFaces[i]) {
//		case CubeFaces::FRONT_FACE:
//			tempFaces[0] = glm::ivec3(0, 0, 0);
//			tempFaces[1] = glm::ivec3(0, 0, 0);
//			break;
//		case CubeFaces::BACK_FACE:
//			tempFaces[2] = glm::ivec3(0, 0, 0);
//			tempFaces[3] = glm::ivec3(0, 0, 0);
//			break;
//		case CubeFaces::LEFT_FACE:
//			tempFaces[4] = glm::ivec3(0, 0, 0);
//			tempFaces[5] = glm::ivec3(0, 0, 0);
//			break;
//		case CubeFaces::RIGHT_FACE:
//			tempFaces[6] = glm::ivec3(0, 0, 0);
//			tempFaces[7] = glm::ivec3(0, 0, 0);
//			break;
//		case CubeFaces::TOP_FACE:
//			tempFaces[8] = glm::ivec3(0, 0, 0);
//			tempFaces[9] = glm::ivec3(0, 0, 0);
//			break;
//		case CubeFaces::BOTTOM_FACE:
//			tempFaces[10] = glm::ivec3(0, 0, 0);
//			tempFaces[11] = glm::ivec3(0, 0, 0);
//			break;
//		}
//	}
//
//	// Remove Faces
//	tempFaces.erase(std::remove_if(tempFaces.begin(),
//		tempFaces.end(),
//		[](glm::ivec3 x) { return (x.x == 0 && x.y == 0 && x.z == 0); }),
//		tempFaces.end());
//
//	ConvertFaces(tempFaces);
//}
//
//void Cube::ConvertFaces(std::vector<glm::ivec3> &vecFaces)
//{
//	_faces.clear();
//	for (size_t i = 0; i < vecFaces.size(); i++)
//	{
//		_faces.push_back(vecFaces[i].x);
//		_faces.push_back(vecFaces[i].y);
//		_faces.push_back(vecFaces[i].z);
//	}
//}
