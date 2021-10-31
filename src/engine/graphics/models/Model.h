#pragma once

#include "Mesh.h"
#include "../shaders/Shader.h"
#include "../Material.h"

#include <assimp/scene.h>

enum class MaterialType
{
	Value,
	Textured,
	TexturedWithSpecular
};

class Model
{
public:
	Model();
	Model(std::shared_ptr<Mesh> mesh);
	Model(char* path);

	// Setters
	void SetMaterial(Material material, bool textured = false, bool specular = false);
	std::vector<std::shared_ptr<Mesh>>& GetMeshes() { return _meshes; };

	virtual void Draw(Shader &shader);
protected:
	std::vector<std::shared_ptr<Mesh>> _meshes;
	std::string _directory;
	Material _material;
	MaterialType _materialType = MaterialType::Value;

	// TODO: Import Model Loading
	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	Material LoadMaterial(aiMaterial* material);
};

