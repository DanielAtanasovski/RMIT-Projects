#include "Scene2.h"

void Scene2::setupBuffers()
{
	// Buffers
	glGenBuffers(1, &_materialIDBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _materialIDBuffer);
	glBufferData(GL_ARRAY_BUFFER, _materialIds.size() * sizeof(int), &_materialIds.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _verticesArray.size() * sizeof(glm::vec3), &_verticesArray.front() , GL_STATIC_DRAW);

	// Attributes
	glGenVertexArrays(1, &_vertexArray);
	glBindVertexArray(_vertexArray);

	// Vertex Positions
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	// Material IDs
	glBindBuffer(GL_ARRAY_BUFFER, _materialIDBuffer);
	glVertexAttribIPointer(1, 1, GL_INT, sizeof(int), 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// EBO
	glGenBuffers(1, &_faceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _faceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _faceIds.size() * sizeof(unsigned int), &_faceIds.front(), GL_STATIC_DRAW);
}

void Scene2::setupMaterials()
{
	_shader->use();
	_shader->setVec3("materials[0].Ambient", glm::vec3(0.8, 0.3, 0.3));
	_shader->setVec3("materials[0].Diffuse", glm::vec3(0.2, 0.2, 0.2));

	_shader->setVec3("materials[1].Ambient", glm::vec3(0.3, 0.8, 0.3));
	_shader->setVec3("materials[1].Diffuse", glm::vec3(0.2, 0.2, 0.2));

	_shader->setVec3("materials[2].Ambient", glm::vec3(0.3, 0.3, 0.8));
	_shader->setVec3("materials[2].Diffuse", glm::vec3(0.5, 0.5, 0.5));
}

void Scene2::DrawMengerSponge()
{
	_shader->use();
	_shader->setMatrix4("viewMatrix", _camera->getViewMatrix());
	_shader->setMatrix4("perspectiveMatrix", _camera->getPerspectiveMatrix());

	glBindVertexArray(_vertexArray);
	glDrawElements(GL_TRIANGLES, _faceIds.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Scene2::Recalculate()
{
	Scene::Recalculate();

	_faceIds.clear();
	_faceIds.shrink_to_fit();
	// Need to change face ids from glm::vec3 of triangles to single array of ids
	for (size_t i = 0; i < _facesArray.size(); i++)
	{
		_faceIds.push_back(_facesArray[i].x);
		_faceIds.push_back(_facesArray[i].y);
		_faceIds.push_back(_facesArray[i].z);
	}

	if (!firstRun) {
		// Update face buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _faceBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _faceIds.size() * sizeof(unsigned int), &_faceIds.front(), GL_STATIC_DRAW);

		// Update vertices buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, _verticesArray.size() * sizeof(glm::vec3), &_verticesArray.front(), GL_STATIC_DRAW);

		// Update materials buffer
		glBindBuffer(GL_ARRAY_BUFFER, _materialIDBuffer);
		glBufferData(GL_ARRAY_BUFFER, _materialIds.size() * sizeof(int), &_materialIds.front(), GL_STATIC_DRAW);

		std::cout << "Material Count: " << _materialIds.size() << std::endl;
		for (size_t i = 0; i < _materialIds.size(); i++)
		{
			std::cout << "ID: " << _materialIds[i] << std::endl;
		}

		std::cout << "Face Count: " << _faceIds.size() << std::endl;
		for (size_t i = 0; i < _faceIds.size(); i++)
		{
			std::cout << "Face: " << _faceIds[i] << std::endl;
		}
	}
	else 
		firstRun = false;
	
}

void Scene2::Run()
{
	DrawMengerSponge();
}

void Scene2::Done()
{
	// Clear Buffers and Shaders
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &_vertexArray);
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_faceBuffer);
	delete _shader;
}

void Scene2::Init(HUD* hud, Camera* camera)
{
	_hud = hud;
	_camera = camera;

	_shader = new Shader("./src/shaders/Colour.vert", "./src/shaders/Colour.frag");

	Recalculate();
	setupBuffers();
	setupMaterials();
}
