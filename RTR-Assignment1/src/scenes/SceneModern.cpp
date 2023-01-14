#include "SceneModern.h"

void SceneModern::Init(HUD* hud, Camera* camera)
{
	_hud = hud;
	_camera = camera;
	_camera->UpdatePosition(glm::vec3(0, 0, 25));

	_shader = new Shader("./src/shaders/MengerShader.vert",
		"./src/shaders/MengerShader.frag",
		"./src/shaders/MengerShader.geom");

	Recalculate();
	SetupBuffers();
	SetupMaterials();
	SetupLights();
}

void SceneModern::Run()
{
	SetupDraw();
	Draw();
}

void SceneModern::Done()
{
	_subdivisions = 0;
	_verticesArray.clear();
	_verticesArray.shrink_to_fit();
	_facesArray.clear();
	_facesArray.shrink_to_fit();
	_faceIds.clear();
	_faceIds.shrink_to_fit();
	// Clear Buffers and Shaders
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &_vertexArray);
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_faceBuffer);
	delete _shader;
}

void SceneModern::Recalculate()
{
	// Generate Sponge
	Scene::Recalculate();

	// Reset old face IDs
	_faceIds.clear();
	_faceIds.shrink_to_fit();

	// Convert facesArray from vec3 to int
	for (size_t i = 0; i < _facesArray.size(); i++)
	{
		_faceIds.push_back(_facesArray[i].x);
		_faceIds.push_back(_facesArray[i].y);
		_faceIds.push_back(_facesArray[i].z);
	}

	// Ensure we are updating buffers after generating them
	if (!firstRun) {
		// Update face buffer
		glBindVertexArray(_vertexArray);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _faceBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _faceIds.size() * sizeof(unsigned int), &_faceIds.front(), GL_STATIC_DRAW);

		// Update vertices buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, _verticesArray.size() * sizeof(glm::vec3), &_verticesArray.front(), GL_STATIC_DRAW);

		// Unbind all
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
		firstRun = false;
}

void SceneModern::SetupBuffers()
{
	// Buffers
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _verticesArray.size() * sizeof(glm::vec3), &_verticesArray.front(), GL_STATIC_DRAW);

	// Attributes
	glGenVertexArrays(1, &_vertexArray);
	glBindVertexArray(_vertexArray);

	// Vertex Positions
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	// Enable
	glEnableVertexAttribArray(0);

	// EBO
	glGenBuffers(1, &_faceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _faceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _faceIds.size() * sizeof(unsigned int), &_faceIds.front(), GL_STATIC_DRAW);

	// Unbind all
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SceneModern::SetupMaterials()
{
	_shader->use();
	_shader->setVec3("materials[0].Ambient", glm::vec3(0.8, 0.3, 0.3));
	_shader->setVec3("materials[0].Diffuse", glm::vec3(0.2, 0.2, 0.2));
	_shader->setVec3("materials[0].Specular", glm::vec3(0.2, 0.2, 0.2));
	_shader->setFloat("materials[0].Shiniess", 45.0f);

	_shader->setVec3("materials[1].Ambient", glm::vec3(0.3, 0.8, 0.3));
	_shader->setVec3("materials[1].Diffuse", glm::vec3(0.2, 0.2, 0.2));
	_shader->setVec3("materials[0].Specular", glm::vec3(0.2, 0.2, 0.2));
	_shader->setFloat("materials[0].Shiniess", 33.0f);

	_shader->setVec3("materials[2].Ambient", glm::vec3(0.3, 0.3, 0.8));
	_shader->setVec3("materials[2].Diffuse", glm::vec3(0.5, 0.5, 0.5));
	_shader->setVec3("materials[0].Specular", glm::vec3(0.2, 0.2, 0.2));
	_shader->setFloat("materials[0].Shiniess", 50.0f);
	glUseProgram(0);
}

void SceneModern::SetupLights()
{
	_shader->use();

	_shader->setInt("NumberOfLights", _numLights);
	for (size_t i = 0; i < _lights.size(); i++)
	{
		Light l = _lights[i];
		std::ostringstream stringStream;
		// Build Light Uniform
		stringStream << "Lights[" << i << "].Type";
		_shader->setInt(stringStream.str().c_str(), (int)l.getType());

		stringStream.str("");
		stringStream << "Lights[" << i << "].Ambient";
		_shader->setVec3(stringStream.str().c_str(), l.getAmbient());

		stringStream.str("");
		stringStream << "Lights[" << i << "].Diffuse";
		_shader->setVec3(stringStream.str().c_str(), l.getDiffuse());

		stringStream.str("");
		stringStream << "Lights[" << i << "].Specular";
		_shader->setVec3(stringStream.str().c_str(), l.getSpecular());

		stringStream.str("");
		stringStream << "Lights[" << i << "].Direction";
		_shader->setVec3(stringStream.str().c_str(), l.getDirection());

		stringStream.str("");
		stringStream << "Lights[" << i << "].Position";
		_shader->setVec3(stringStream.str().c_str(), l.getPosition());

		stringStream.str("");
		stringStream << "Lights[" << i << "].Constant";
		_shader->setFloat(stringStream.str().c_str(), l.getConstant());

		stringStream.str("");
		stringStream << "Lights[" << i << "].Linear";
		_shader->setFloat(stringStream.str().c_str(), l.getLinear());

		stringStream.str("");
		stringStream << "Lights[" << i << "].Quadratic";
		_shader->setFloat(stringStream.str().c_str(), l.getQuadratic());
	}

	glUseProgram(0);
}

void SceneModern::SetupDraw()
{
	_shader->use();

	// Update Matrices
	_shader->setMatrix4("viewMatrix", _camera->getViewMatrix());
	_shader->setMatrix4("perspectiveMatrix", _camera->getPerspectiveMatrix());
	_shader->setMatrix4("modelMatrix", _modelMatrix);

	// Update Lights
	_shader->setVec3("Lights[0].Direction", _camera->GetFront());
	_shader->setVec3("Lights[0].Position", _camera->GetPosition());
}

void SceneModern::Draw()
{
	glBindVertexArray(_vertexArray);
	glDrawElements(GL_TRIANGLES, _faceIds.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void SceneModern::SetLightCount(int count)
{
	_numLights = count;

	// Set within range
	if (_numLights < 0)
		_numLights = 0;
	if (_numLights > _lights.size())
		_numLights = _lights.size();

}
