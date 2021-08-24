#include "Scene1.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <string>


void Scene1::Init(HUD* hud, Camera* camera)
{
	_hud = hud;
	_camera = camera;

	_lighting = false;
	_cullFaces = true;
	_depthTest = true;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	_hud->SetDrawAttributes(_depthTest, _lighting, _cullFaces);
	_hud->SetSubdivisions(_subdivisions);

	// Directional Camera
	GLfloat ambient[] = { 0.5, 0.5, 0.4, 0.2 };
	GLfloat diffuse[] = { 0.5, 0.5, 0.2, 0.2 };
	GLfloat specular[] = { 0.4, 0.4, 0.4, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);

	Recalculate();
}

void Scene1::Run()
{
	// Update Directional Light
	//GLfloat position[] = { 0, 0, 0, 1.0 };
	//std::cout << glm::to_string(_camera->GetPosition()) << std::endl;
	//glPushMatrix();
	//glLoadIdentity();
	//glLightfv(GL_LIGHT0, GL_POSITION, position);
	//glPopMatrix();

	DrawMengerSpongeEfficient();
}

void Scene1::Done()
{
	glDisable(GL_LIGHTING);
}

void Scene1::Recalculate()
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

	unsigned int data = _verticesArray.capacity() * sizeof(glm::vec3) + sizeof(_verticesArray);
	_hud->SetData(_triangleCount, _cubeCount, _verticesArray.size(), data);
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

			// Get Cube Vertices
			Cube cube = Cube(
				glm::vec3( xMin + ((col * xInterval) + xOffset),
					y, zMin + ((row * zInterval) + zOffset)),
				size, CalculateDisabledFaces(row, col, top));

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
	glPushMatrix();

	if (_lighting)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);

	// Draw Shape
	glBegin(GL_TRIANGLES);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	int lastMatIndex = 99;
	for (size_t i = 0; i < _facesArray.size(); i++)
	{
		// Get Triangle Vertexes
		glm::ivec3 faceIndex = _facesArray[i];
		glm::vec3 pointA = _verticesArray[faceIndex.x];
		glm::vec3 pointB = _verticesArray[faceIndex.y];
		glm::vec3 pointC = _verticesArray[faceIndex.z];

		// Material
		Material material = _CUBE_MATERIALS[_materialIds[i]];
		if (_lighting)
		{ 
			if (_materialIds[i] != lastMatIndex) {
			
				// Ambient
				GLfloat materialConvert[] = { 0, 0, 0, 0 };
				materialConvert[0] = material.GetAmbient().r;
				materialConvert[1] = material.GetAmbient().g;
				materialConvert[2] = material.GetAmbient().b;
				materialConvert[3] = material.GetAmbient().a;
				glMaterialfv(GL_FRONT, GL_AMBIENT, materialConvert);

				// Diffuse
				materialConvert[0] = material.GetDiffuse().r;
				materialConvert[1] = material.GetDiffuse().g;
				materialConvert[2] = material.GetDiffuse().b;
				materialConvert[3] = material.GetDiffuse().a;
				glMaterialfv(GL_FRONT, GL_DIFFUSE, materialConvert);

				// Specular
				materialConvert[0] = material.GetSpecular().r;
				materialConvert[1] = material.GetSpecular().g;
				materialConvert[2] = material.GetSpecular().b;
				materialConvert[3] = material.GetSpecular().a;
				glMaterialfv(GL_FRONT, GL_SPECULAR, materialConvert);

				//Shininess
				glMaterialf(GL_FRONT, GL_SHININESS, material.GetShininess());

				lastMatIndex = _materialIds[i];
			}
		}
		else {
			if (_materialIds[i] != lastMatIndex) {

				glm::vec3 finalColour = glm::normalize(material.GetAmbient() + material.GetDiffuse());
				glColor3f(finalColour.r, finalColour.g, finalColour.b);
				lastMatIndex = _materialIds[i];
			}
		}


		//// Determine Colour
		//if (pointA.x == pointB.x && pointA.x == pointC.x) {
		//	// Left / Right
		//	_newColour = _CUBE_COLOURS[0];
		//}
		//else if (pointA.y == pointB.y && pointA.y == pointC.y) {
		//	// Top / Bottom
		//	_newColour = _CUBE_COLOURS[1];
		//}
		//else if (pointA.z == pointB.z && pointA.z == pointC.z) {
		//	// Front / Back
		//	_newColour = _CUBE_COLOURS[2];
		//}

		// Set Colour
		//if (_newColour.r != _currentColour.r || _newColour.g != _currentColour.g || _newColour.b != _currentColour.b) {
		//	_currentColour = _newColour;
		//	glColor3f(_currentColour.r, _currentColour.g, _currentColour.b);
		//}

		glm::vec3 u = pointB - pointA;
		glm::vec3 v = pointC - pointA;

		glm::vec3 finalNormal = glm::normalize(glm::vec3((u.y * v.z) - (u.z * v.y),
			(u.z * v.x) - (u.x * v.z),
			(u.x * v.y) - (u.y * v.x)));

		glNormal3f(finalNormal.x, finalNormal.y, finalNormal.z);

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

	//if (_lighting)
	//	glDisable(GL_LIGHTING);

	glPopMatrix();
}
