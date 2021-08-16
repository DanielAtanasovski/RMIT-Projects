// Daniel Atanasovski
#pragma once

#include <glad/glad.h>
#include <sdl/SDL.h>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera(float width, float height) : _position(glm::vec3(0,0,5)) {

		_perspectiveMatrix = glm::perspective(glm::radians<float>(45.0f), width / height, 0.1f, 100.0f);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(_perspectiveMatrix));
		glMatrixMode(GL_MODELVIEW);
		_viewMatrix = glm::lookAt(_position, _position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
		glLoadMatrixf(glm::value_ptr(_viewMatrix));
	};
	~Camera() {};
	void UpdatePosition(glm::vec3 newPosition) { 

		_position = newPosition;
		_viewMatrix = glm::lookAt(_position, _position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(_perspectiveMatrix));
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(_viewMatrix));
	};
	glm::vec3 GetPosition() { return _position; };

private:
	glm::mat4 _perspectiveMatrix;
	glm::mat4 _viewMatrix;
	glm::vec3 _position;
};