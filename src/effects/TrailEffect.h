#pragma once
#include <vector>
#include "Particle.h"
#include "ParticleSystem.h"
#include "../math/Vector2.h"

class TrailEffect : public ParticleSystem
{
public:
	void start() { canSpawn = true; };
	void stop() { canSpawn = false; };
	void update(float deltaTime) override;
	void draw() override;
	void updateState(Vector2 position, Vector2 direction) { this->position = position; this->direction = direction; };
private:
	Vector2 direction = Vector2(0,0);
	std::vector<Particle*> particles;
	float spawnStep = 0.1f;
	float currentSpawnTime = 0.0f;
	bool canSpawn = false;

};

