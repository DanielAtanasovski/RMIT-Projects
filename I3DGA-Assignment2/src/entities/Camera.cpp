#include "Camera.h"
#include <iostream>
#include "Player.h"
#include "../manager/Input.h"

#if _WIN32
#   include <Windows.h>
#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

Camera::Camera(Game& game) : game(game){
	updateCameraPosition();
}

void Camera::update(float deltaTime) {
	Vector2 mousePos = Input::getMousePosition();
	float mouseX = mousePos.x - game.getWidth() / 2;
	float mouseY = mousePos.y - game.getHeight() / 2;

	// Ratio
	float yawChangeRate = mouseX / (game.getWidth() / 2);
	float pitchChangeRate = mouseY / (game.getHeight() / 2);

	yaw += yawChangeRate * YAW_MAX_SPEED * deltaTime;
	pitch -= pitchChangeRate * PITCH_MAX_SPEED * deltaTime;

	pitch = Math::clamp(pitch, -89, 89);

	if (Input::onPressed('w')) {
		position += forwardVector * FORWARD_MOVE_SPEED * deltaTime;
	}

	if (Input::onPressed('s')) {
		position += forwardVector * -FORWARD_MOVE_SPEED * deltaTime;
	}

	if (Input::onPressed('a')) {
		position += rightVector * -SIDE_MOVE_SPEED * deltaTime;
	}

	if (Input::onPressed('d')) {
		position += rightVector * SIDE_MOVE_SPEED * deltaTime;
	}

	updateCameraPosition();
}

void Camera::draw() {
	gluLookAt(
		position.x, position.y, position.z,
		position.x + forwardVector.x, position.y + forwardVector.y, position.z + forwardVector.z,
		0, 1, 0
	);

	glutPostRedisplay();
}

void Camera::updateCameraPosition() {
	forwardVector.x = cosf(Math::degToRad(yaw)) * cosf(Math::degToRad(pitch));
	forwardVector.y = sinf(Math::degToRad(pitch));
	forwardVector.z = sinf(Math::degToRad(yaw)) * cosf(Math::degToRad(pitch));
	forwardVector.normalised();

	rightVector = Math::crossProduct(forwardVector, Vector3(0, 1, 0)).normalised();
	upVector = Math::crossProduct(rightVector, forwardVector).normalised();
}