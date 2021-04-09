#pragma once
#include "../physics/CollidableEntity.h"
#include "../math/Math.h"

class Asteroid : public CollidableEntity
{
public:
	Asteroid(Vector2 position, float rotation);
	~Asteroid() {};
	void draw() override;
	void update(float deltaTime) override;

private:
	const float MIN_SPEED = 20.0f;
	const float MAX_SPEED = 40.0f;

	Vector2 direction;
	float speed = Math::getRandomFloat(MIN_SPEED, MAX_SPEED);
};