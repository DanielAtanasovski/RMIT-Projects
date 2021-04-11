#pragma once
#include "../physics/CollidableEntity.h"
#include "../math/Math.h"
#include <vector>

class Asteroid : public CollidableEntity
{
public:
	Asteroid(Vector2 position, float rotation);
	~Asteroid() {};
	void generateAsteroid();
	void drawAsteroid();
	void draw() override;
	void update(float deltaTime) override;

private:
	
	const int MAX_POINTS = 14; // Amount of points used to draw asteroid
	const float MAX_SIZE = 14.0f; // Biggest size
	const float MIN_SIZE = 6.0f; // smallest size
	const float MAX_SIZE_OFFSET = 2.0f; // max difference between each point
	const float MIN_SIZE_OFFSET = -1.5f;
	const float MIN_SPEED = 20.0f;
	const float MAX_SPEED = 40.0f;
	const float MIN_ROTATION_SPEED = 10.0f;
	const float MAX_ROTATION_SPEED = 25.0f;

	const Vector3 FILL_COLOUR = Vector3(0.4f, 0.4f, 0.4f);
	const Vector3 OUTLINE_COLOUR = Vector3(0.8f, 0.8f, 0.8f);

	const bool rotateClockwise = Math::getRandomBool();
	const float size = Math::getRandomFloat(MIN_SIZE, MAX_SIZE);
	const float speed = Math::getRandomFloat(MIN_SPEED, MAX_SPEED);
	const float rotationSpeed = Math::getRandomFloat(MIN_ROTATION_SPEED, MAX_ROTATION_SPEED);
	std::vector<Vector2> drawPoints = std::vector<Vector2>();
	Vector2 direction;
	
};