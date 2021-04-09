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
	const float MAX_SIZE_OFFSET = 3.0f; // max difference between each point
	const float MIN_SIZE_OFFSET = -3.0f;
	const float MIN_SPEED = 20.0f;
	const float MAX_SPEED = 40.0f;

	const float size = Math::getRandomFloat(MIN_SIZE, MAX_SIZE);
	const float speed = Math::getRandomFloat(MIN_SPEED, MAX_SPEED);
	std::vector<Vector2> drawPoints = std::vector<Vector2>();
	Vector2 direction;
	
};