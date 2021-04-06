#pragma once
#include "../entity/Player.h"
#include "../math/Vector2.h"

class Arena
{

public:
	Arena(Player* player);
	~Arena();
	void draw();
	void update();
	// Consts
	const float WIDTH = 199;
	const float HEIGHT = 199;

private:
	// Reference
	Player* player = nullptr;
	const float WARNING_DISTANCE = 30.0f;
	// Walls
	const Vector2 TOP_LEFT_POINT = Vector2(-WIDTH/2, HEIGHT/2);
	const Vector2 BOTTOM_LEFT_POINT = Vector2(-WIDTH/2, -HEIGHT/2);
	const Vector2 TOP_RIGHT_POINT = Vector2(WIDTH/2, HEIGHT/2);
	const Vector2 BOTTOM_RIGHT_POINT = Vector2(WIDTH/2, -HEIGHT/2);

	const Vector3 DEFAULT_LINE_COLOUR = Vector3(1.0f, 1.0f, 1.0f);
	const Vector3 WARNING_LINE_COLOUR = Vector3(1.0f, 0.5f, 0.0f);
	Vector3 topLineColour = Vector3(DEFAULT_LINE_COLOUR);
	Vector3 rightLineColour = Vector3(DEFAULT_LINE_COLOUR);
	Vector3 bottomLineColour = Vector3(DEFAULT_LINE_COLOUR);
	Vector3 leftLineColour = Vector3(DEFAULT_LINE_COLOUR);
	//
	void lineCheck();
};


