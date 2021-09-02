#include "Model.h"

Model::Model()
{
}

Model::Model(Mesh mesh)
{
	_meshes.push_back(mesh);
}

Model::Model(char* path)
{
	// Load Model 
	throw "Unimplemented Model Loading!";
}

void Model::Draw(Shader &shader)
{
	for (size_t i = 0; i < _meshes.size(); i++)
	{
		_meshes[i].Draw(shader);
	}
}
