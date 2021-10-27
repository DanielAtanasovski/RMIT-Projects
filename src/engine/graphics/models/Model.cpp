#include "Model.h"

Model::Model()
{
	_material = {
		glm::vec3(1),
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
	glm::vec3(1),
	glm::vec3(1),
	glm::vec3(1),
	0.0f,
	glm::vec3(0),
	};

	_materialMapped = {
		glm::vec3(1), 0, 0, 0
	};
}

Model::Model(char* path)
{
	// Load Model 
	throw "Unimplemented Model Loading!";
}

void Model::Draw(Shader &shader)
{
	// TODO: Use Renderer to set uniforms, as it caches the current state
	shader.use();
	if (_isMaterialMapped) {
		shader.setVec3("material.Ambient", _material.Ambient);
		// Textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _materialMapped.DiffuseID);
		shader.setInt("material.Diffuse", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _materialMapped.SpecularID);
		shader.setInt("material.Specular", 1);

		shader.setFloat("material.Shininess", _materialMapped.Shininess);
	}
	else {
		shader.setVec3("material.Ambient", _material.Ambient);
		shader.setVec3("material.Diffuse", _material.Diffuse);
		shader.setVec3("material.Specular", _material.Specular);
		shader.setFloat("material.Shininess", _material.Shininess);
	}

	for (size_t i = 0; i < _meshes.size(); i++)
	{
		_meshes[i].Draw(shader);
	}
}
