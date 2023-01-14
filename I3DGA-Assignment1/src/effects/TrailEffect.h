#pragma once
#include <vector>
#include "Particle.h"
#include "../math/Vector2.h"

class TrailEffect : public Entity
{
public:
	TrailEffect(Vector2 position, Vector3 colour) { this->position = position; this->particlesColour = colour; };
	~TrailEffect() { particles.clear(); };
	void start() { canSpawn = true; };
	void stop() { canSpawn = false; };
	void update(float deltaTime) override;
	void draw() override;
	void updateState(Vector2 position, Vector2 direction) { this->position = position; this->direction = direction; };
private:
	Vector2 direction = Vector2(0,0);
	Vector3 particlesColour = Vector3(0,0,0);
	std::vector<Particle*> particles;
	float spawnStep = 0.1f;
	float currentSpawnTime = 0.0f;
	bool canSpawn = false;

	const float PARTICLE_SPEED = 80.0f;
	const float PARTICLE_MAX_SIZE = 20.0f;
	const float PARTICLE_MIN_SIZE = 0.5f;
	const float PARTICLE_DURATION = 1.0f;
};

