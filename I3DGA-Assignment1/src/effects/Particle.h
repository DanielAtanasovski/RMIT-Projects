#pragma once
#include "../entity/Entity.h"
#include "../math/Vector3.h"

class Particle : public Entity
{
public:
	Particle(Vector2 position, Vector2 direction, Vector3 colour, float SPEED, float maxLifeTime, float SIZE);
	Particle(Vector2 position, Vector2 direction, Vector3 colourStart, Vector3 colourEnd, float SPEED, float maxLifeTime, float SIZE);
	~Particle() {};

	void draw() override;
	void update(float deltaTime) override;
	bool isDone() { return done; }
private:
	bool done = false;
	Vector3 colourStart = Vector3(1, 1, 1);
	Vector3 colourEnd = Vector3(1,1,1);
	Vector3 colourCurrent = colourStart;
	Vector3 colourStep = Vector3();

	Vector2 direction = Vector2(0, 0);
	float SPEED = 80.0f;
	float maxLifetime = 1.0f;
	float currentLifetime = 0.0f;

	float sizeStart = 1.0f;
	float sizeEnd = 0.0f;
	float sizeCurrent = sizeStart;
	float sizeStep = 0.1f;
	float currentTime = 0.0f;
};

