#include "CubeMesh.h"

CubeMesh::CubeMesh()
{
	CalculateBoxMesh();
	SetupMesh();
}

void CubeMesh::CalculateBoxMesh()
{
	// Vertices
	// Duplicate Vertices so as to get lighting to work
	_vertices = {
		// Back Face
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0,0) },
		{ glm::vec3(0.5f , -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1,0) },
		{ glm::vec3(0.5f ,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1,1) },
		{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0,1) },
		// Front Face
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f,  0.0f, 1.0f), glm::vec2(0,0) },
		{ glm::vec3(0.5f , -0.5f,  0.5f), glm::vec3(0.0f,  0.0f, 1.0f), glm::vec2(1,0) },
		{ glm::vec3(0.5f ,  0.5f,  0.5f), glm::vec3(0.0f,  0.0f, 1.0f), glm::vec2(1,1) },
		{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  0.0f, 1.0f), glm::vec2(0,1) },
		// Left Face
		{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1,1) },
		{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0,1) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0,0) },
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1,0) },
		// Right Face
		{ glm::vec3(0.5f ,  0.5f,  0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0,1) },
		{ glm::vec3(0.5f ,  0.5f, -0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(1,1) },
		{ glm::vec3(0.5f , -0.5f, -0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(1,0) },
		{ glm::vec3(0.5f , -0.5f,  0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0,0) },
		// Bottom Face
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(1,1) },
		{ glm::vec3(0.5f , -0.5f, -0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(1,0) },
		{ glm::vec3(0.5f , -0.5f,  0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0,0) },
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0,1) },
		// Top Face
		{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(1,0) },
		{ glm::vec3(0.5f ,  0.5f, -0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(1,1) },
		{ glm::vec3(0.5f ,  0.5f,  0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0,1) },
		{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0,0) },
	};
	
	// Indices
	_indices = {
		0,   2, 1 , // Back
		0,   3, 2 ,
		4,   5, 6 , // Front
		6,   7, 4 ,
		8,   9, 10, // Left
		10, 11, 8 ,
		12, 14, 13, // Right
		12, 15, 14,
		16, 17, 18, // Bottom
		18, 19, 16,
		20, 22, 21, // Top
		20, 23, 22
	};
}
