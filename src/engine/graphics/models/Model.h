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

	virtual void Draw(Shader &shader);
protected:
	std::vector<Mesh> _meshes;
	std::string directory;

	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	Material LoadMaterial(aiMaterial* material);

};

