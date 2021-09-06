#include "Model.h"

Model::Model()
{
	_material = {
		glm::vec3(0),
		glm::vec3(0),
		glm::vec3(0),
		0.0f,
		glm::vec3(0),
	};
}

Model::Model(Mesh mesh)
{
	_meshes.push_back(mesh);

	_material = {
	glm::vec3(0),
	glm::vec3(0),
	glm::vec3(0),
	0.0f,
	glm::vec3(0),
	};
}

Model::Model(char* path)
{
	// Load Model 
	throw "Unimplemented Model Loading!";
}

void Model::Draw(Shader &shader)
{
	shader.use();
	shader.setVec3("material.Ambient", _material.Ambient);
	shader.setVec3("material.Diffuse", _material.Diffuse);
	shader.setVec3("material.Specular", _material.Specular);
	shader.setFloat("material.Shininess", _material.Shininess);
	for (size_t i = 0; i < _meshes.size(); i++)
	{
		_meshes[i].Draw(shader);
	}
}
