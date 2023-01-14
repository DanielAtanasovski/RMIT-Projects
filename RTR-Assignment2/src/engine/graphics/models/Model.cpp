#include "Model.h"

Model::Model()
{
	_material = {
		glm::vec3(1),
		glm::vec3(0),
		glm::vec3(0),
		0.0f,
		0,
		0
	};
}

Model::Model(std::shared_ptr<Mesh> mesh)
{
	_meshes.push_back(mesh);

	_material = {
	glm::vec3(1),
	glm::vec3(1),
	glm::vec3(1),
	0.0f,
	0,
	0
	};
}

Model::Model(char* path)
{
	// Load Model 
	throw "Unimplemented Model Loading!";
}

void Model::SetMaterial(Material material, bool textured, bool specular)
{
	_material = material; 
	if (textured) {
		if (specular)
			_materialType = MaterialType::TexturedWithSpecular;
		else
			_materialType = MaterialType::Textured;
	} else
		_materialType = MaterialType::Value;
}

void Model::Draw(Shader &shader)
{
	// TODO: Use Renderer to set uniforms, as it caches the current state
	shader.use();
	switch (_materialType)
	{
	case MaterialType::Value:
		shader.setVec3("material.Ambient", _material.Ambient);
		shader.setVec3("material.Diffuse", _material.Diffuse);
		shader.setVec3("material.Specular", _material.Specular);
		shader.setFloat("material.Shininess", _material.Shininess);
		break;
	case MaterialType::Textured:
		shader.setVec3("material.Ambient", _material.Ambient);
		// Diffuse Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _material.DiffuseID);
		shader.setInt("material.Diffuse", 0);
		shader.setVec3("material.Specular", _material.Specular);
		shader.setFloat("material.Shininess", _material.Shininess);
		break;
	case MaterialType::TexturedWithSpecular:
		shader.setVec3("material.Ambient", _material.Ambient);
		// Diffuse Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _material.DiffuseID);
		shader.setInt("material.Diffuse", 0);
		// Specular Texture
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _material.SpecularID);
		shader.setInt("material.Specular", 1);

		shader.setFloat("material.Shininess", _material.Shininess);
		break;
	}


	for (size_t i = 0; i < _meshes.size(); i++)
	{
		_meshes[i]->Draw(shader);
	}
}
