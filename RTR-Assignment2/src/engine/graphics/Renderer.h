#pragma once

#include <unordered_map>
#include "models/Model.h"
#include "../entities/Camera.h"

struct RenderBatch {
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	// TODO Added list of textures
	// std::vector<Texture> textures
	// unsigned int textureCount


};

class Renderer {
public:
	void Init();

	void BeginBatch();
	void EndBatch();
	void Flush();

	void DrawModel(Shader& shader, Model& model);

	void SetCamera(std::shared_ptr<Camera> camera);

private:
	std::unordered_map<Shader, std::vector<Model>, ShaderHashFunction> renderShaderQueue;
	std::shared_ptr<Camera> _camera;
	

	// Uniforms Optimisation
	// Cache current values on CPU and compare with new changes
	// to determine whether to update GPU is necessary
	//std::unordered_map<const char*, float> floatUniforms;
	//std::unordered_map<const char*, float> mat4Uniforms;
	//std::unordered_map<const char*, float> vec3Uniforms;
};

