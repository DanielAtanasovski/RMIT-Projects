#pragma once
#include <vector>
#include "Particle.h"
#include "../math/Vector2.h"

class ExplosionEffect : public Entity
{
public:
	ExplosionEffect(Vector2 position, Vector3 colour, int amountOfParticles);
	~ExplosionEffect() { particles.clear(); };
	void start() { canSpawn = true; };
	void stop() { canSpawn = false; };
	bool getDone() { return done; }
	void update(float deltaTime) override;
	void draw() override;
private:
	Vector3 particlesColour = Vector3(0, 0, 0);
	std::vector<Particle*> particles;
	int amountOfParticles = 10;
	bool canSpawn = false;
	bool done = false;

	const float PARTICLE_MAX_SPEED = 80.0f;
	const float PARTICLE_MIN_SPEED = 60.0f;
	const float PARTICLE_MAX_SIZE = 20.0f;
	const float PARTICLE_MIN_SIZE = 0.0f;
	const float PARTICLE_MIN_DURATION = 0.5f;
	const float PARTICLE_MAX_DURATION = 1.0f;
};

