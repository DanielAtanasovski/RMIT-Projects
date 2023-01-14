#include "Scene4.h"

void Scene4::Init(HUD* hud, Camera* camera)
{
	_hud = hud;
	_camera = camera;
	_camera->UpdatePosition(glm::vec3(0, 0, 80));

	_shader = new Shader("./src/shaders/InstancedMengerShader.vert",
		"./src/shaders/InstancedMengerShader.frag",
		"./src/shaders/InstancedMengerShader.geom");

	glShadeModel(GL_SMOOTH);
	Recalculate();

	// Translate Matrices
	for (size_t i = 0; i < _instanceModelMatrices.size(); i++)
	{
		_instanceModelMatrices[i] = glm::translate(_instanceModelMatrices[i], _modelTranslationValue[i]);
	}

	SetupBuffers();
	SetupMaterials();
	SetupLights();
}

void Scene4::Run()
{
	SceneModern::Run();
}

void Scene4::Done()
{
	SceneModern::Done();
	_instanceModelMatrices.fill(glm::mat4(1));
}

void Scene4::Recalculate()
{
	SceneModern::Recalculate();
}

void Scene4::SetupDraw()
{
	_shader->use();

	// Update Matrices
	_shader->setMatrix4("viewMatrix", _camera->getViewMatrix());
	_shader->setMatrix4("perspectiveMatrix", _camera->getPerspectiveMatrix());

	// Update Lights
	_shader->setVec3("Lights[0].Direction", _camera->GetFront());
	_shader->setVec3("Lights[0].Position", _camera->GetPosition());
}

void Scene4::Draw()
{
	glBindVertexArray(_vertexArray);
	glDrawElementsInstanced(GL_TRIANGLES, _faceIds.size(), GL_UNSIGNED_INT, 0, (GLsizei)9);
	glBindVertexArray(0);
}

void Scene4::Update(unsigned int td_milli)
{
	float step = td_milli / 1000.0f;
	// Rotate Model Matrixces
	for (size_t i = 0; i < _instanceModelMatrices.size(); i++)
	{
		_instanceModelMatrices[i] = glm::rotate(_instanceModelMatrices[i],
			glm::radians(step * _rotationSpeed), _modelRotationDirection[i]);
	}

	// Update Buffer
	glBindBuffer(GL_ARRAY_BUFFER, _instancedModelMatricesBuffer);
	glBufferData(GL_ARRAY_BUFFER, _instanceModelMatrices.size() * sizeof(glm::mat4),
		&_instanceModelMatrices.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Scene4::SetupBuffers()
{
	// Buffers 
	// Vertices
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _verticesArray.size() * sizeof(glm::vec3),
		&_verticesArray.front(), GL_STATIC_DRAW);

	// Matrices
	glGenBuffers(1, &_instancedModelMatricesBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _instancedModelMatricesBuffer);
	glBufferData(GL_ARRAY_BUFFER, _instanceModelMatrices.size() * sizeof(glm::mat4),
		&_instanceModelMatrices.front(), GL_STATIC_DRAW);

	// Attributes
	glGenVertexArrays(1, &_vertexArray);
	glBindVertexArray(_vertexArray);

	// Vertex Positions
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	// Matrix Points
	glBindBuffer(GL_ARRAY_BUFFER, _instancedModelMatricesBuffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 0));
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 4));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);

	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 12));
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);

	// EBO
	glGenBuffers(1, &_faceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _faceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _faceIds.size() * sizeof(unsigned int), &_faceIds.front(), GL_STATIC_DRAW);

	// Unbind all
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Scene4::SetupMaterials()
{
	SceneModern::SetupMaterials();
}

void Scene4::SetupLights()
{
	SceneModern::SetupLights();
}
