// Daniel Atanasovski
#pragma once

#include <glad/glad.h>
#include <sdl/SDL.h>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float DEFAULT_YAW = -90.0f;
const float DEFAULT_PITCH = 0.0f;
const float DEFAULT_SPEED = -90.0f;
const glm::vec3 DEFAULT_POSITION = glm::vec3(0, 0, 10);
const glm::vec3 DEFAULT_UP = glm::vec3(0,1,0);

class Camera
{
public:
	Camera(glm::vec3 position = DEFAULT_POSITION, glm::vec3 up = DEFAULT_UP,
		float yaw = DEFAULT_YAW, float pitch = DEFAULT_PITCH) {
		_position = position;
		_up = up;
		_yaw = yaw;
		_pitch = pitch;
		UpdateCamera();
	}

	// Setters
	void SetPosition(glm::vec3 position) { _position = position; };
	void SetDirection(float xRot, float yRot);

	// Getters
	glm::mat4 GetViewMatrix() { return glm::lookAt(_position, _position + _front, _up); }
	glm::vec3 GetPosition() { return _position; };
	glm::vec3 GetFront() { return _front; }
	glm::vec3 GetUp() { return _up; }

private:
	void UpdateCamera();
	glm::vec3 _position;
	glm::vec3 _worldUp;

	glm::vec3 _front;
	glm::vec3 _right;
	glm::vec3 _up;

	// Controls
	float _yawSensitivity = 0.15f;
	float _pitchSensitivity = 0.15f;
	float _yaw = -90.0f;
	float _pitch = 0.0f;
};