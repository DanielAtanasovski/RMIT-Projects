#include "Scene.h"
#include <glad/glad.h>
#include <glm/gtx/hash.hpp>
#include <unordered_map>

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

void Scene::Recalculate()
{
	_verticesArray.clear();
	_verticesArray.shrink_to_fit();
	_facesArray.clear();
	_facesArray.shrink_to_fit();
	_materialIds.clear();
	_materialIds.shrink_to_fit();

	_triangleCount = 0;
	_cubeCount = 0;
	if (_subdivisions > 0) {
		CalculateMengerSponge(_position, _size, _subdivisions - 1);
	}
	else {
		Cube cube = Cube(_position, glm::vec3(_size));

		// Convert local face ids to global face ids
		std::vector<glm::ivec3> cubeFaces = cube.getFaces();
		for (size_t i = 0; i < cubeFaces.size(); i++)
		{
			cubeFaces[i] += _verticesArray.size();
		}

		// Update global vertices array
		_verticesArray.insert(_verticesArray.end(), cube.getVertices().begin(), cube.getVertices().end());

		// Update Global Arrays
		_materialIds.insert(_materialIds.end(), cube.getMaterialIds().begin(), cube.getMaterialIds().end());
		_facesArray.insert(_facesArray.end(), cubeFaces.begin(), cubeFaces.end());

		// Update Stats
		_triangleCount += cube.getTriangleCount();
		_cubeCount++;
	}

	PruneVertices();

	unsigned int data = (unsigned int)_verticesArray.size() * sizeof(glm::vec3);
	_hud->SetData((int)_triangleCount, _cubeCount, (int)_verticesArray.size(), data);
}

void Scene::CalculateMengerSponge(glm::vec3 position, float size, int subdivisions)
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

void Scene::CalculateOuterLayer(float xMin, float xMax, float y, float zMin, float zMax, bool top)
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

			// Get Cube Vertices
			Cube cube = Cube(
				glm::vec3(xMin + ((col * xInterval) + xOffset),
					y, zMin + ((row * zInterval) + zOffset)),
				size, CalculateDisabledFaces((int)row, (int)col, top));

			// Convert local face ids to global face ids
			std::vector<glm::ivec3> cubeFaces = cube.getFaces();
			for (size_t i = 0; i < cubeFaces.size(); i++)
			{
				cubeFaces[i] += _verticesArray.size();
			}

			// Update global vertices array
			_verticesArray.insert(_verticesArray.end(), cube.getVertices().begin(), cube.getVertices().end());

			// Update Global Arrays
			_materialIds.insert(_materialIds.end(), cube.getMaterialIds().begin(), cube.getMaterialIds().end());
			_facesArray.insert(_facesArray.end(), cubeFaces.begin(), cubeFaces.end());

			// Update Stats
			_triangleCount += cube.getTriangleCount();
			_cubeCount++;
		}
	}
}

void Scene::CalculateMiddleLayer(float xMin, float xMax, float y, float zMin, float zMax)
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

			Cube cube = Cube(
				glm::vec3(xMin + ((col * xInterval) + xOffset), y, zMin + ((row * zInterval) + zOffset)),
				size, disabledFaces);

			// Convert local face ids to global face ids
			std::vector<glm::ivec3> cubeFaces = cube.getFaces();
			for (size_t i = 0; i < cubeFaces.size(); i++)
			{
				cubeFaces[i] += _verticesArray.size();
			}

			// Update global vertices array
			_verticesArray.insert(_verticesArray.end(), cube.getVertices().begin(), cube.getVertices().end());

			// Update Global Arrays
			_materialIds.insert(_materialIds.end(), cube.getMaterialIds().begin(), cube.getMaterialIds().end());
			_facesArray.insert(_facesArray.end(), cubeFaces.begin(), cubeFaces.end());

			// Update Stats
			_triangleCount += cube.getTriangleCount();
			_cubeCount++;
		}
	}
}

std::vector<CubeFaces> Scene::CalculateDisabledFaces(int row, int col, bool topLayer)
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

void Scene::PruneVertices()
{
	int vCount = 0;

	std::vector<glm::vec3> newVerticesArray = std::vector<glm::vec3>();
	std::vector<unsigned int> reIndexArray = std::vector<unsigned int>();
	std::unordered_map<glm::vec3, unsigned int> lookupMap = std::unordered_map<glm::vec3, unsigned int>();

	// Setup new vertices array and convert indices
	for (size_t i = 0; i < _verticesArray.size(); i++)
	{
		// Check if vert is accounted for
		auto found = lookupMap.find(_verticesArray[i]);
		if (found != lookupMap.end()) {
			// Make sure to add to reIndex array
			reIndexArray.push_back(found->second);
		}
		else {
			// Add to lookup table and re
			lookupMap.insert({ _verticesArray[i], vCount });
			newVerticesArray.push_back(_verticesArray[i]);
			reIndexArray.push_back(vCount);
			vCount++;
		}
	}

	// Update Index Array
	for (size_t i = 0; i < _facesArray.size(); i++)
	{
		_facesArray[i].x = reIndexArray[_facesArray[i].x];
		_facesArray[i].y = reIndexArray[_facesArray[i].y];
		_facesArray[i].z = reIndexArray[_facesArray[i].z];
	}
	_verticesArray = newVerticesArray;
}
