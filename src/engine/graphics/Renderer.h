#pragma once

#include <unordered_map>
#include "models/Model.h"

class Renderer {
public:
	void Init();

	void BeginBatch();
	void EndBatch();
	void Flush();

private:
	std::unordered_map<Shader, std::vector<Model>> renderShader;

	// Uniforms Optimisation
	// Cache current values on CPU and compare with new changes
	// to determine whether to update GPU is necessary
	//std::unordered_map<const char*, float> floatUniforms;
	//std::unordered_map<const char*, float> mat4Uniforms;
	//std::unordered_map<const char*, float> vec3Uniforms;
};