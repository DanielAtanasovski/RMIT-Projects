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
	void SetMaterial(Material material) { _material = material; _isMaterialMapped = false; };
	void SetMaterial(MaterialMapped materialMapped) { _materialMapped = materialMapped; _isMaterialMapped = true; }

	virtual void Draw(Shader &shader);
protected:
	std::vector<Mesh> _meshes;
	std::string _directory;
	Material _material;
	MaterialMapped _materialMapped;
	bool _isMaterialMapped = false;

	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	Material LoadMaterial(aiMaterial* material);
};

