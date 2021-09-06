#pragma once

#include "Mesh.h"
#include "../shaders/Shader.h"
#include "../Material.h"

#include <assimp/scene.h>

class Model
{
public:
	Model();
	Model(Mesh mesh);
	Model(char* path);

	// Setters
	void SetMaterial(Material material) { _material = material; };

	virtual void Draw(Shader &shader);
protected:
	std::vector<Mesh> _meshes;
	std::string _directory;
	Material _material;

	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	Material LoadMaterial(aiMaterial* material);
};

