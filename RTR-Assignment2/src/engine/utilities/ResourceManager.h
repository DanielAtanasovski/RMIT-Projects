#pragma once
#include <vector>
#include <memory>
#include "../graphics/shaders/Shader.h"
#include <unordered_map>
#include <array>

class ResourceManager {
public:
	ResourceManager();
	std::shared_ptr<Shader> LoadShader(Shader shader);
	const char* LoadTextureFile(const char* filePath);
	unsigned int LoadTexture(const char* filePath);
	unsigned int LoadCubeMapTexture(std::array<const char*, 6> filePaths);
private:
	std::vector<std::shared_ptr<Shader>> _shaders = std::vector<std::shared_ptr<Shader>>();
	std::unordered_map<const char*, unsigned int> _textures;

	std::shared_ptr<Shader> FindOrCreateShader(Shader shader);
};