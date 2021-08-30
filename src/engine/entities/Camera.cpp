#include "Camera.h"

void Camera::SetDirection(float xRot, float yRot)
{
	_yaw += xRot * _yawSensitivity;
	_pitch += -yRot * _pitchSensitivity;

	// Clamp pitch So Camera doesnt flip
	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	UpdateCamera();
}

void Camera::UpdateCamera()
{
	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	_front = glm::normalize(front);
	_right = glm::normalize(glm::cross(_front, _up));
	_up = glm::normalize(glm::cross(_right, _front));
}
