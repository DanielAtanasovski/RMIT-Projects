#pragma once
#include "../math/Vector2.h"
#include "../math/Vector3.h"

class Player
{
public:
	Player(float x, float y);
	Player();
	~Player();
	void draw();
	void update();

private:
	Vector2 position = Vector2(0, 0);
	float rotation = 45.0f;
	void getInput();
	void move();
	void boundsCheck();
	Vector2 inputVector;
	float velocity = 0.0f;

	// Settings
	// TODO: Move to Game options class
	// Controls
	const char KEY_UP = 'W';
	const char KEY_DOWN = 'S';
	const char SHOOT = ' ';
	const char KEY_LEFT = 'A';
	const char KEY_RIGHT = 'D';
	// Stats
	const float ROTATE_SPEED = 5.0f;
	const float MOVE_SPEED = 2.0f;
	// Colours
	const Vector3 OUTLINE_COLOUR = Vector3(1.0f, 0.0f, 0.0f);
	const Vector3 FILL_COLOUR = Vector3(1.0f, 1.0f, 1.0f);
	// Drawing
	const Vector2 DRAW_TOP_POINT = Vector2(0, 5);
	const Vector2 DRAW_LEFT_POINT = Vector2(-5, -10);
	const Vector2 DRAW_MID_POINT = Vector2(0, -5);
	const Vector2 DRAW_RIGHT_POINT = Vector2(5, -10);
};

