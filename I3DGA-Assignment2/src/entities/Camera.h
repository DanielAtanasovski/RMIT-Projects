#pragma once
#include "Entity.h"
#include "../Game.h"

class Game;

class Camera : public Entity {
public:
	Camera(Game& game);
	~Camera() {  };
	void update(float deltaTime) override;
	void draw() override;
	Vector3 getForward() { return forwardVector; };
	Vector3 getRight() { return rightVector; };
	Vector3 getUp() { return upVector; };
	float getYaw() { return yaw; }
	float getRoll() { return roll; }
	float getPitch() { return pitch; }
	void reset() { position = Vector3(); yaw = -90; roll = pitch = 0; }

private:
	Game& game;
	void updateCameraPosition();
	Vector3 targetPosition = Vector3(0,0,0);
	Vector3 forwardVector = Vector3(0, 0, -1);
	Vector3 rightVector = Vector3(1, 0, 0);
	Vector3 upVector = Vector3(0, 1, 0);

	float yaw = -90;
	float roll = 0;
	float pitch = 0;
	 
	const float SIDE_MOVE_SPEED = 20.0f;
	const float FORWARD_MOVE_SPEED = 40.0f;
	const float YAW_MAX_SPEED = 80.0f;
	const float ROLL_SPEED = 20.0f;
	const float PITCH_MAX_SPEED = 60.0f;
};