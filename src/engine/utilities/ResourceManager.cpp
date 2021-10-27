#include "ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

ResourceManager::ResourceManager()
{
	_shaders = std::vector<std::shared_ptr<Shader>>();
	_textures = std::unordered_map<const char*, unsigned int>();
}

std::shared_ptr<Shader> ResourceManager::LoadShader(Shader shader)
{
	return FindOrCreateShader(shader);
}

const char* ResourceManager::LoadTextureFile(const char* filePath)
{
	return nullptr;
}

unsigned int ResourceManager::LoadTexture(const char* filePath)
{
	// Return Texture buffer id if it exists
	if (_textures.size() != 0)
		if (_textures.find(filePath) != _textures.end())
			return _textures[filePath];
	
	// Load Texture
	stbi_set_flip_vertically_on_load(true);
	int width, height, channels;
	unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);

	if (data == NULL) {
		std::cout << "FAILED TO LOAD TEXTURE FILE: " << filePath << std::endl;
		exit(-1);
	}

	// Create Texture Buffer
	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	if (channels > 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	// mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	return id;
}

unsigned int ResourceManager::LoadCubeMapTexture(std::array<const char*, 6> filePaths) {
	// Create Texture Buffer
	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	// Load Texture
	stbi_set_flip_vertically_on_load(false);
	int width, height, channels;
	for (size_t i = 0; i < 6; i++)
	{
		unsigned char* data = stbi_load(filePaths[i], &width, &height, &channels, 0);

		if (channels > 3)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else 
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return id;
}

std::shared_ptr<Shader> ResourceManager::FindOrCreateShader(Shader shader)
{
	for (size_t i = 0; i < _shaders.size(); i++)
	{
		if (*_shaders[i] == shader)
			return _shaders[i];
	}
	std::shared_ptr<Shader> shaderPtr;
	if (shader.GetGeometryPath() == "")
		shaderPtr = std::make_shared<Shader>(shader.GetVertexPath().c_str(), shader.GetFragmentPath().c_str());
	else
		shaderPtr = std::make_shared<Shader>(shader.GetVertexPath().c_str(), shader.GetFragmentPath().c_str(), shader.GetGeometryPath().c_str());
	_shaders.push_back(shaderPtr);
	return shaderPtr;
}
