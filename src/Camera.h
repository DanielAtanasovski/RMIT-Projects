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
	Camera(float width, float height) {
		glViewport(0, 0, width, height);
		_perspectiveMatrix = glm::perspective(glm::radians<float>(45.0f), width / height, 0.1f, 100.0f);
		_viewMatrix = glm::lookAt(_position, _position + _cameraTarget, _up);

	};
	~Camera() {};
	void UpdatePosition(glm::vec3 newPosition) { 
		_position = newPosition;
		_viewMatrix = glm::lookAt(_position, _position + _cameraTarget, _up);
	};

	void UpdateDirection(float xRot, float yRot) {
		_yaw += xRot * _yawSensitivity;
		_pitch += -yRot * _pitchSensitivity;

		if (_pitch > 89.0f)
			_pitch = 89.0f;
		if (_pitch < -89.0f)
			_pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		direction.y = sin(glm::radians(_pitch));
		direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_cameraTarget = glm::normalize(direction);
		UpdatePosition(_position);
	}

	glm::vec3 GetPosition() { return _position; };
	float GetYawSpeed() { return _yawSensitivity; }
	float GetPitchSpeed() { return _pitchSensitivity; }
	glm::vec3 GetFront() { return _cameraTarget; }
	glm::vec3 GetUp() { return _cameraUp; }
	glm::mat4 getViewMatrix() { return _viewMatrix; }
	glm::mat4 getPerspectiveMatrix() { return _perspectiveMatrix; }

private:
	glm::mat4 _perspectiveMatrix;
	glm::mat4 _viewMatrix;
	glm::vec3 _position = glm::vec3(0, 0, 15);
	glm::vec3 _cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 _cameraDirection = glm::normalize(_position - _cameraTarget);
	glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 _cameraRight = glm::normalize(glm::cross(_up, _cameraDirection));
	glm::vec3 _cameraUp = glm::cross(_cameraDirection, _cameraRight);

	float _yawSensitivity = 0.15f;
	float _pitchSensitivity = 0.15f;

	float _yaw = -90.0f;
	float _pitch = 0.0f;


};