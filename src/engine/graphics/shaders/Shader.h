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
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
	Shader(const char* vertexPath, const char* fragmentPath); // No Geometry Shader
	// Activate Shader
	void use();

	// Uniform Functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMatrix4(const std::string& name, glm::mat4 value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;

	const std::string GetVertexPath() const { return _vertexPath; }
	const std::string GetFragmentPath() const { return _fragmentPath; }
	const std::string GetGeometryPath() const { return _geometryPath; }

	inline bool operator==(const Shader& other)
	{
		if (other.GetVertexPath() == _vertexPath)
			if (other.GetFragmentPath() == _fragmentPath)
				if (other.GetGeometryPath() == _geometryPath)
					return true;
		return false;
	};

private:
	std::string _vertexPath = "";
	std::string _fragmentPath = "";
	std::string _geometryPath = "";
};

class ShaderHashFunction {
public:
	size_t operator()(const Shader& shader) const {
		return shader.GetFragmentPath().length() + shader.GetGeometryPath().length()
			+ shader.GetVertexPath().length();
	}
};