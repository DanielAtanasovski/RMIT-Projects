#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <array>
#include <vector>
#include "Material.h"

enum CubeFaces
{
	TOP_FACE,
	BOTTOM_FACE,
	FRONT_FACE,
	BACK_FACE,
	LEFT_FACE,
	RIGHT_FACE
};


class Cube {
public:
	Cube(glm::vec3 position, glm::vec3 size = glm::vec3(1, 1, 1), std::vector<CubeFaces> disableFaces = {});
	~Cube() { };
	void draw();
	glm::vec3 getPosition() { return _position; }
	glm::vec3 getSize() { return _size; }
	int getTriangleCount() { return _currentCubeIndices.size(); }

	std::vector<glm::vec3> getVertices() { return _currentCubeVertices; };
	std::vector<glm::ivec3> getFaces() { return _currentCubeIndices; };

protected:
	glm::vec3 _size;
	glm::vec3 _position;
	glm::mat4 _localModelMatrix;
	glm::mat4 _scaleMatrix;
	glm::mat4 _positionMatrix;
	std::vector<CubeFaces> _disabledFaces;
	std::vector<glm::ivec3> _currentCubeIndices;
	std::vector<glm::vec3> _currentCubeVertices;
private:
	void calculateCurrentCubeIndices();
	glm::vec3 _currentColour = glm::vec3(1.0f);
	glm::vec3 _newColour = glm::vec3(1.0f);

	const glm::vec3 _CUBE_VERTICES[8] = {
			glm::vec3(-0.5, -0.5,  0.5), // 0. Close Bottom Left
			glm::vec3(0.5, -0.5,  0.5), // 1. Close Bottom Right
			glm::vec3(0.5,  0.5,  0.5), // 2. Close Top Right
			glm::vec3(-0.5,  0.5,  0.5), // 3. Close Top Left
			glm::vec3(-0.5, -0.5, -0.5), // 4. Far Bottom Left
			glm::vec3(0.5, -0.5, -0.5), // 5. Far Bottom Right
			glm::vec3(0.5,  0.5, -0.5), // 6. Far Top Right
			glm::vec3(-0.5,  0.5, -0.5)  // 7. Far Top Left
	}; 

	// To Draw Rectangles
	const std::array<glm::ivec3, 12> _CUBE_INDICES = {
		glm::ivec3(0,1,2), // Front Face
		glm::ivec3(0,2,3),
		glm::ivec3(4,6,5), // Back Face
		glm::ivec3(4,7,6),
		glm::ivec3(0,3,7), // Left Face
		glm::ivec3(4,0,7),
		glm::ivec3(1,5,6), // Right Face
		glm::ivec3(6,2,1),
		glm::ivec3(3,2,6), // Top Face
		glm::ivec3(3,6,7),
		glm::ivec3(0,5,1), // Bottom Face
		glm::ivec3(0,4,5)
	};

	const std::array<glm::vec3, 6> _CUBE_COLOURS = {
		glm::vec3(1.0f, 0.3f,  0.3f),
		glm::vec3(1.0f, 0.3f,  1.0f),
		glm::vec3(0.3f, 0.3f,  1.0f),
		glm::vec3(0.3f, 1.0f,  0.3f),
		glm::vec3(1.0f, 1.0f,  0.3f),
		glm::vec3(1.0f, 0.5f,  0.3f)
	};

	const std::array<Material, 3> _CUBE_MATERIALS = {
		Material(glm::vec4(0.8 ,0.3,0.3,1), glm::vec4(1,1,1,1), // X-Axis Material
			glm::vec4(1), glm::vec4(1), glm::vec4(1)),
		Material(glm::vec4(0.8 ,0.3,0.3,1), glm::vec4(1,1,1,1), // Y-Axis Material
			glm::vec4(1), glm::vec4(1), glm::vec4(1)),
		Material(glm::vec4(0.8 ,0.3,0.3,1), glm::vec4(1,1,1,1), // Z-Axis Material
			glm::vec4(1), glm::vec4(1), glm::vec4(1))
	};
};