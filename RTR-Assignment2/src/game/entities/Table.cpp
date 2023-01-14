#include "Table.h"

Table::Table(std::shared_ptr<ResourceManager> resourceManager) : Entity(Model(std::make_shared<CubeMesh>()), resourceManager->LoadShader(Shader("./assets/shaders/StandardTextured.vert", "./assets/shaders/StandardTextured.frag")))
{
	tableElements = std::array<std::unique_ptr<CubeEntity>, 6> {
		std::make_unique<CubeEntity>(resourceManager),
		std::make_unique<CubeEntity>(resourceManager),
		std::make_unique<CubeEntity>(resourceManager),
		std::make_unique<CubeEntity>(resourceManager),
		std::make_unique<CubeEntity>(resourceManager),
		std::make_unique<CubeEntity>(resourceManager)
	};

	// Layout Elements
	// Set Position / Scale / Rotation
	// Ground
	tableElements[0]->SetPosition(glm::vec3(0, 0, 0));
	tableElements[0]->SetScale(glm::vec3(20, 1, 30));
	// Right Wall
	tableElements[1]->SetPosition(glm::vec3(10.25f, 1, 0));
	tableElements[1]->SetScale(glm::vec3(0.5f, 1, 30));
	// Left Wall
	tableElements[2]->SetPosition(glm::vec3(-10.25f, 1, 0));
	tableElements[2]->SetScale(glm::vec3(0.5f, 1, 30));
	// Bottom Wall
	tableElements[3]->SetPosition(glm::vec3(0, 1, -15.25f));
	tableElements[3]->SetScale(glm::vec3(20, 1, 0.5f));
	// Top Wall
	tableElements[4]->SetPosition(glm::vec3(0, 1, 15.25f));
	tableElements[4]->SetScale(glm::vec3(20, 1, 0.5f));
	// Launch Wall
	tableElements[5]->SetPosition(glm::vec3(8.5, 1, 2.5));
	tableElements[5]->SetScale(glm::vec3(0.5f, 1, 25));

	for (size_t i = 0; i < tableElements.size(); i++)
	{
		// Set Shader
		tableElements[i]->SetShader(resourceManager->LoadShader(Shader("./assets/shaders/StandardTextured.vert", "./assets/shaders/StandardTextured.frag")));
		// Set Material
		tableElements[i]->SetMaterial({
			glm::vec3(0.4f),
			glm::vec3(0),
			glm::vec3(0),
			32.0f,
			resourceManager->LoadTexture("./assets/textures/bricks.jpg"),
			resourceManager->LoadTexture("./assets/textures/bricks_specular.jpg"),
			}, true, true);
		// Update Tex Coords
		tableElements[i]->GetModel().GetMeshes()[0]->Recalculate(tableElements[i]->GetScale());
	}
}

void Table::UpdateViewMatrix(glm::mat4 matrix) {
	for (size_t i = 0; i < tableElements.size(); i++)
	{
		tableElements[i]->SetViewMatrix(matrix);
	}
}

void Table::UpdatePerspectiveMatrix(glm::mat4 matrix) {
	for (size_t i = 0; i < tableElements.size(); i++)
	{
		tableElements[i]->SetPerspectiveMatrix(matrix);
	}
}

void Table::Draw() {
	for (size_t i = 0; i < tableElements.size(); i++)
	{
		tableElements[i]->Draw();
	}
}
