#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/ext/matrix_float4x4.hpp>

class Shader
{
public:
	// Program ID
	unsigned int ID;
	// Builds Shader
	Shader(const char* vertexPath, const char* fragmentPath);
	// Activate Shader
	void use();

	// Uniform Functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMatrix4(const std::string& name, glm::mat4 value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
};