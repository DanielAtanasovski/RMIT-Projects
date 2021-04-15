#pragma once
#include "../math/Vector2.h"
#include "../math/Vector3.h"
#include "../physics/CollidableEntity.h"
#include "../effects/TrailEffect.h"

class Player : public CollidableEntity
{
public:
	Player(Vector2 position, float rotation);
	~Player() { delete trailEffect; };
	void draw() override;
	void update(float deltaTime) override;

private:
	void getInput();
	void move(float deltaTime);
	void shoot();
	Vector2 inputVector;
	float velocity = 0.0f;
	TrailEffect* trailEffect;
	bool isMoving = false;

	// Controls
	const char KEY_UP = 'W';
	const char KEY_SHOOT_1 = ' ';
	const char KEY_LEFT = 'A';
	const char KEY_RIGHT = 'D';
	// Stats
	const float ROTATE_SPEED = 200.0f;
	const float MOVE_SPEED = 90.0f;
	// Colours
	const Vector3 OUTLINE_COLOUR = Vector3(0.0f, 0.0f, 1.0f);
	const Vector3 FILL_COLOUR = Vector3(1.0f, 1.0f, 1.0f);
	const Vector3 TRAIL_COLOUR = Vector3(1.0f, 0.5f, 0.0f);
	// Drawing
	const Vector2 DRAW_TOP_POINT = Vector2(0, 7.5);
	const Vector2 DRAW_LEFT_POINT = Vector2(-5, -7.5);
	const Vector2 DRAW_MID_POINT = Vector2(0, -2.5);
	const Vector2 DRAW_RIGHT_POINT = Vector2(5, -7.5);
};

