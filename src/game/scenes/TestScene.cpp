#include "TestScene.h"

TestScene::TestScene(std::shared_ptr<Input> input, std::shared_ptr<Renderer> renderer) : _input(input), _renderer(renderer)
{

}

void TestScene::Init(std::shared_ptr<ResourceManager> resourceManager)
{
	// Entities
	_camera = std::make_unique<Camera>();
	_centerCube = std::make_unique<CubeEntity>(resourceManager);
	_centerCube->SetShader(resourceManager->LoadShader(Shader("./assets/shaders/StandardTextured.vert", "./assets/shaders/StandardTextured.frag")));
	_centerCube->SetMaterial({
		glm::vec3(0.4f),
		resourceManager->LoadTexture("./assets/textures/bricks.jpg"),
		resourceManager->LoadTexture("./assets/textures/bricks_specular.jpg"),
		32.0f,
	});
	_verticalLightCube = std::make_unique<LightCube>(glm::vec3(0, 10, 0), resourceManager);
	_horizonalLightCube = std::make_unique<LightCube>(glm::vec3(10, 2, 10), resourceManager);

	// Skybox
	_skyBox = std::make_unique<SkyBoxEntity>(_filePaths, resourceManager);

	// Transformations
	_camera->SetPosition(glm::vec3(0, 0, 10));
	_centerCube->SetScale(glm::vec3(5, 5, 5));

	// TODO: Move to Renderer
	// Set Perspective Matrix 
	_centerCube->SetPerspectiveMatrix(_perspectiveMatrix);
	_horizonalLightCube->SetPerspectiveMatrix(_perspectiveMatrix);
	_verticalLightCube->SetPerspectiveMatrix(_perspectiveMatrix);
	_skyBox->SetPerspectiveMatrix(_perspectiveMatrix);

	// Add lights
	_pointLights.push_back(_horizonalLightCube->GetLight());
	_pointLights.push_back(_verticalLightCube->GetLight());
}

void TestScene::Update(float delta)
{
	UpdateCamera(delta);
	_centerCube->SetViewMatrix(_camera->GetViewMatrix());
	_horizonalLightCube->SetViewMatrix(_camera->GetViewMatrix());
	_verticalLightCube->SetViewMatrix(_camera->GetViewMatrix());

	// No translation view matrix
	glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(_camera->GetViewMatrix()));
	_skyBox->SetViewMatrix(viewNoTranslation);

	_timeCount += delta;
	_horizonalLightCube->SetPosition(glm::vec3(10 * glm::sin(_timeCount), 2, 10 * glm::cos(_timeCount)));
	_verticalLightCube->SetPosition(glm::vec3(0, 10 * glm::sin(_timeCount), 10 * glm::cos(_timeCount)));
}

void TestScene::Draw()
{
	std::cout << _pointLights.size() << std::endl;

	// Update Lights
	Shader& shader = _centerCube->GetShader();
	shader.use();
	std::ostringstream stringStream;
	for (size_t i = 0; i < _pointLights.size(); i++)
	{	
		std::shared_ptr<PointLight> light = _pointLights[i];

		// Update Light Components
		stringStream << "pLights[" << i << "].Position";
		shader.setVec3(stringStream.str().c_str(), light->Position);

		stringStream.str("");
		stringStream << "pLights[" << i << "].Ambient";
		shader.setVec3(stringStream.str().c_str(), light->Ambient);

		stringStream.str("");
		stringStream << "pLights[" << i << "].Diffuse";
		shader.setVec3(stringStream.str().c_str(), light->Diffuse);

		stringStream.str("");
		stringStream << "pLights[" << i << "].Specular";
		shader.setVec3(stringStream.str().c_str(), light->Specular);

		stringStream.str("");
		stringStream << "pLights[" << i << "].Constant";
		shader.setFloat(stringStream.str().c_str(), light->Constant);

		stringStream.str("");
		stringStream << "pLights[" << i << "].Linear";
		shader.setFloat(stringStream.str().c_str(), light->Linear);

		stringStream.str("");
		stringStream << "pLights[" << i << "].Quadratic";
		shader.setFloat(stringStream.str().c_str(), light->Quadratic);
	}
	shader.setInt("numLights", _pointLights.size());
	shader.setVec3("viewPos", _camera->GetPosition());
	//_lightCube->SetViewMatrix(_camera->GetViewMatrix());


	// Draw Entities
	_skyBox->Draw();
	_centerCube->Draw();
	_horizonalLightCube->Draw();
	_verticalLightCube->Draw();
	
}

void TestScene::Done()
{
}

void TestScene::UpdateCamera(float delta)
{
	glm::vec3 _inputDirection = glm::vec3(0);
	// Strafe 
	if (_input->IsKeyPressed(SDL_SCANCODE_A)) {
		_inputDirection.x = -1;
	}
	else if (_input->IsKeyPressed(SDL_SCANCODE_D)) {
		_inputDirection.x = 1;
	}

	// Vertical
	if (_input->IsKeyPressed(SDL_SCANCODE_E)) {
		_inputDirection.y = -1;
	}
	else if (_input->IsKeyPressed(SDL_SCANCODE_Q)) {
		_inputDirection.y = 1;
	}

	// Forward
	if (_input->IsKeyPressed(SDL_SCANCODE_S)) {
		_inputDirection.z = -1;
	}
	else if (_input->IsKeyPressed(SDL_SCANCODE_W)) {
		_inputDirection.z = 1;
	}

	_camera->SetDirection(_input->GetLastMouseMotion().x, _input->GetLastMouseMotion().y);
	_camera->Move(_inputDirection, delta);
}
