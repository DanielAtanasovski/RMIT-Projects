#include "Scene2.h"

void Scene2::setupBuffers()
{
	// Buffers
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _verticesArray.size() * sizeof(glm::vec3), &_verticesArray.front() , GL_STATIC_DRAW);

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

void Scene2::setupMaterials()
{
	_shader->use();
	_shader->setVec3("materials[0].Ambient", glm::vec3(0.8, 0.3, 0.3));
	_shader->setVec3("materials[0].Diffuse", glm::vec3(0.2, 0.2, 0.2));

	_shader->setVec3("materials[1].Ambient", glm::vec3(0.3, 0.8, 0.3));
	_shader->setVec3("materials[1].Diffuse", glm::vec3(0.2, 0.2, 0.2));

	_shader->setVec3("materials[2].Ambient", glm::vec3(0.3, 0.3, 0.8));
	_shader->setVec3("materials[2].Diffuse", glm::vec3(0.5, 0.5, 0.5));
	glUseProgram(0);
}

void Scene2::setupLights()
{

	_shader->use();

	// TODO: Move to function
	_shader->setInt("NumberOfLights", _numLights);
	Light l = _lights[0];
	_shader->setInt("Lights[0].Type", (int)l.getType());
	_shader->setVec3("Lights[0].Ambient", l.getAmbient());
	_shader->setVec3("Lights[0].Diffuse", l.getDiffuse());
	_shader->setVec3("Lights[0].Specular", l.getSpecular());
	_shader->setVec3("Lights[0].Direction", _camera->GetFront());
	_shader->setVec3("Lights[0].Position", _camera->GetPosition());
	_shader->setFloat("Lights[0].Constant", l.getConstant());
	_shader->setFloat("Lights[0].Linear", l.getLinear());
	_shader->setFloat("Lights[0].Quadratic", l.getQuadratic());

	glUseProgram(0);
}

void Scene2::DrawMengerSponge()
{
	_shader->use();
	_shader->setMatrix4("viewMatrix", _camera->getViewMatrix());
	_shader->setMatrix4("perspectiveMatrix", _camera->getPerspectiveMatrix());
	_shader->setMatrix4("modelMatrix", glm::mat4(1));
	_shader->setVec3("Lights[0].Direction", _camera->GetFront());
	_shader->setVec3("LightCameraDirection", _camera->GetFront());
	_shader->setVec3("Lights[0].Position", _camera->GetPosition());

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

void Scene2::Run()
{
	DrawMengerSponge();
}

void Scene2::Done()
{
	// Clear Buffers and Shaders
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &_vertexArray);
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_faceBuffer);
	delete _shader;
}

void Scene2::Init(HUD* hud, Camera* camera)
{
	_hud = hud;
	_camera = camera;

	_shader = new Shader("./src/shaders/MengerShader.vert",
		"./src/shaders/MengerShader.frag",
		"./src/shaders/MengerShader.geom");
	glShadeModel(GL_SMOOTH);
	Recalculate();
	setupBuffers();
	setupMaterials();
	setupLights();
}
