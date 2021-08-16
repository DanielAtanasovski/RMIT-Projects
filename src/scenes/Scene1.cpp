#include "Scene1.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>


void Scene1::Init()
{
	_lighting = false;
	_cullFaces = true;
	_depthTest = true;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// TODO:Enable Lights
	_triangleCount = 0;
	_cubeCount = 0;
	CalculateMengerSponge(_position, _size, _subdivisions);
	std::cout << "Final Triangle Count: " << _triangleCount << std::endl;
	std::cout << "Final Cube Count: " << _cubeCount << std::endl;
}

void Scene1::Run()
{
	// TODO: Convert Menger cube vertexes to be in world coordinates to make it easier
	// 	   to return an array of vertexes
	//glPushMatrix();
	//glMatrixMode(GL_MODELVIEW);
	//glm::mat4 _localModelMatrix = glm::mat4(1.0f);
	//glm::mat4 _scaleMatrix = glm::scale(_localModelMatrix, glm::vec3(1.0f));
	//glm::mat4 _positionMatrix = glm::translate(_localModelMatrix, _position);
	//_localModelMatrix = _positionMatrix * _scaleMatrix;
	//glMultMatrixf(glm::value_ptr(_localModelMatrix)); // Multiply so as to get contribute to projectionMatrix
	for (size_t i = 0; i < _mengerCubesArray.size(); i++)
	{
		_mengerCubesArray[i]->draw();
	}
	//glPopMatrix();
}

void Scene1::Done()
{
	glDisable(GL_LIGHTING);
}

void Scene1::Recalculate()
{
	_mengerCubesArray.clear();
	_mengerCubesArray.shrink_to_fit();
	_triangleCount = 0;
	_cubeCount = 0;
	CalculateMengerSponge(_position, _size, _subdivisions);
	std::cout << "Final Triangle Count: " << _triangleCount << std::endl;
	std::cout << "Final Cube Count: " << _cubeCount << std::endl;
}

void Scene1::CalculateMengerSponge(glm::vec3 position, float size, int subdivisions)
{
	float offset = size / 3; // Interval for 3 cubes an Axis
	float halfOffset = offset / 2; // Center Points
	if (subdivisions > 0) {
		for (size_t zIndex = 0; zIndex < 3; zIndex++)
		{
			for (size_t yIndex = 0; yIndex < 3; yIndex++)
			{
				for (size_t xIndex = 0; xIndex < 3; xIndex++)
				{
					// Skip a couple of iterations for empty blocks
					if (((zIndex == 0 || zIndex == 2) && ((xIndex == 1 && yIndex == 1))) || // FRONT / BACK CENTER
						((zIndex == 1) && (yIndex == 1)) || // CENTER CENTER BLOCK
						((zIndex == 1) && (yIndex == 0 || yIndex == 2) && (xIndex == 1)) // LEFT / RIGHT CENTER
						)
						continue;

					CalculateMengerSponge(glm::vec3(
						position.x + ((xIndex * offset) - offset),
						position.y + ((yIndex * offset) - offset),
						position.z + ((zIndex * offset) - offset)),
						offset, subdivisions - 1);
				}
			}
		}
	}
	else {
		CalculateOuterLayer(position.x - offset - halfOffset, position.x + offset + halfOffset, position.y + offset, position.z - offset - halfOffset, position.z + offset + halfOffset, true);
		CalculateMiddleLayer(position.x - offset - halfOffset, position.x + offset + halfOffset, position.y, position.z - offset - halfOffset, position.z + offset + halfOffset);
		CalculateOuterLayer(position.x - offset - halfOffset, position.x + offset + halfOffset, position.y - offset, position.z - offset - halfOffset, position.z + offset + halfOffset, false);
	}
}

void Scene1::CalculateOuterLayer(float xMin, float xMax, float y, float zMin, float zMax, bool top)
{

	// (length) / 3 cubes along x-axis = length of each cube
	// length of each cube / 2 = offset to use DrawCenteredCube
	float xInterval = ((xMax - xMin) / 3);
	float xOffset = xInterval / 2;
	float zInterval = ((zMax - zMin) / 3);
	float zOffset = zInterval / 2;
	glm::vec3 size = glm::vec3(xInterval);
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			// Skip Center Block
			if (row == 1 && col == 1)
				continue; // No Center Block

			Cube* cube = new Cube(
				glm::vec3( xMin + ((col * xInterval) + xOffset),
					y, zMin + ((row * zInterval) + zOffset)),
				size, CalculateDisabledFaces(row, col, top));

			_mengerCubesArray.push_back(cube);
			_triangleCount += cube->getTriangleCount();
			_cubeCount++;
		}
	}
}

void Scene1::CalculateMiddleLayer(float xMin, float xMax, float y, float zMin, float zMax)
{
	float xInterval = ((xMax - xMin) / 3);
	float xOffset = xInterval / 2;
	float zInterval = ((zMax - zMin) / 3);
	float zOffset = zInterval / 2;
	glm::vec3 size = glm::vec3(xInterval);
	std::vector<CubeFaces> disabledFaces = std::vector<CubeFaces>{ CubeFaces::TOP_FACE, CubeFaces::BOTTOM_FACE };
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			// if center
			if (row == 0 && col == 1 ||
				row == 1 && col == 0 ||
				row == 1 && col == 1 ||
				row == 1 && col == 2 ||
				row == 2 && col == 1)
				continue;

			Cube* cube = new Cube(
				glm::vec3(xMin + ((col * xInterval) + xOffset), y, zMin + ((row * zInterval) + zOffset)),
				size, disabledFaces);

			_mengerCubesArray.push_back(cube);
			_triangleCount += cube->getTriangleCount();
			_cubeCount++;
		}
	}
}

std::vector<CubeFaces> Scene1::CalculateDisabledFaces(int row, int col, bool topLayer)
{
	std::vector<CubeFaces> disabledFaces;
	if (topLayer) {
		if (row == 0 && col == 0)
			disabledFaces = std::vector<CubeFaces>{ CubeFaces::FRONT_FACE, CubeFaces::RIGHT_FACE, CubeFaces::BOTTOM_FACE }; // BACK LEFT
		if ((row == 0 || row == 2) && col == 1)
			disabledFaces = std::vector<CubeFaces>{ CubeFaces::LEFT_FACE, CubeFaces::RIGHT_FACE }; // BACK / FRONT CENTER
		if (row == 0 && col == 2)
			disabledFaces = std::vector<CubeFaces>{ CubeFaces::FRONT_FACE, CubeFaces::LEFT_FACE, CubeFaces::BOTTOM_FACE }; // BACK RIGHT
		if (row == 1 && (col == 0 || col == 2))
			disabledFaces = std::vector<CubeFaces>{ CubeFaces::FRONT_FACE, CubeFaces::BACK_FACE }; // MIDDLE LEFT / RIGHT
		if (row == 2 && col == 0)
			disabledFaces = std::vector<CubeFaces>{ CubeFaces::BACK_FACE, CubeFaces::RIGHT_FACE, CubeFaces::BOTTOM_FACE }; // FRONT LEFT
		if (row == 2 && col == 2)
			disabledFaces = std::vector<CubeFaces>{ CubeFaces::BACK_FACE, CubeFaces::LEFT_FACE, CubeFaces::BOTTOM_FACE }; // FRONT RIGHT
	}
	else {
		if (row == 0 && col == 0)
			disabledFaces = std::vector<CubeFaces>{ CubeFaces::FRONT_FACE, CubeFaces::RIGHT_FACE, CubeFaces::TOP_FACE }; // BACK LEFT
		if ((row == 0 || row == 2) && col == 1)
			disabledFaces = std::vector<CubeFaces>{ CubeFaces::LEFT_FACE, CubeFaces::RIGHT_FACE }; // BACK / FRONT CENTER
		if (row == 0 && col == 2)
			disabledFaces = std::vector<CubeFaces>{ CubeFaces::FRONT_FACE, CubeFaces::LEFT_FACE, CubeFaces::TOP_FACE }; // BACK RIGHT
		if (row == 1 && (col == 0 || col == 2))
			disabledFaces = std::vector<CubeFaces>{ CubeFaces::FRONT_FACE, CubeFaces::BACK_FACE }; // MIDDLE LEFT / RIGHT
		if (row == 2 && col == 0)
			disabledFaces = std::vector<CubeFaces>{ CubeFaces::BACK_FACE, CubeFaces::RIGHT_FACE, CubeFaces::TOP_FACE }; // FRONT LEFT
		if (row == 2 && col == 2)
			disabledFaces = std::vector<CubeFaces>{ CubeFaces::BACK_FACE, CubeFaces::LEFT_FACE, CubeFaces::TOP_FACE }; // FRONT RIGHT
	}
	return disabledFaces;
}

void Scene1::DrawMengerSpongeEfficient()
{
	for (size_t i = 0; i < _mengerCubesArray.size(); i++)
	{
		_mengerCubesArray[i]->draw();
	}
}
