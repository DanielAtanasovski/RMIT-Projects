#pragma once
#include "../entity/Entity.h"
#include "../math/Vector3.h"

class Particle : public Entity
{
public:
	Particle(Vector2 position, Vector2 direction, Vector3 colour, float speed, float maxLifeTime, float size);
	~Particle() {};

	void draw() override;
	void update(float deltaTime) override;
	bool isDone() { return done; }
private:
	Vector3 colour = Vector3(1, 1, 1);
	Vector2 direction = Vector2(0, 0);
	float speed = 80.0f;
	float maxLifetime = 1.0f;
	float currentLifetime = 0.0f;
	float size = 1.0f;
	bool done = false;
};

