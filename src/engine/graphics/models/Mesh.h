#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float2.hpp>
#include <string>
#include <vector>
#include "../shaders/Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh {
public:
	Mesh();
	~Mesh() { glDeleteBuffers(1, &_VBO); glDeleteBuffers(1, &_EBO); glDeleteBuffers(1, &_VAO); };
	Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures);
	virtual void Draw(Shader& shader);
	virtual void Recalculate(glm::vec3 scale);

protected:
	unsigned int _VAO, _VBO, _EBO;
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
	std::vector<Texture> _textures;

	virtual void SetupMesh();
	void RebuildMesh();
};