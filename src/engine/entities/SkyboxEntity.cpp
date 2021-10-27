#include "SkyboxEntity.h"


SkyBoxEntity::SkyBoxEntity(std::array<const char*, 6> filePaths, std::shared_ptr<ResourceManager> resourceManager) : Entity(Model(), resourceManager->LoadShader(Shader("./assets/shaders/Skybox.vert", "./assets/shaders/Skybox.frag")))
{
	setupDraw();
	_cubemapID = resourceManager->LoadCubeMapTexture(filePaths);
}

void SkyBoxEntity::Draw()
{
	glDepthFunc(GL_LEQUAL);
	_shader->use();
	
	glBindVertexArray(_skyboxVAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
}

void SkyBoxEntity::setupDraw()
{
	glGenVertexArrays(1, &_skyboxVAO);
	glGenBuffers(1, &_skyboxVBO);
	glBindVertexArray(_skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_skyboxVertices), &_skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}
