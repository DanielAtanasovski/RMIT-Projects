#include "TrailEffect.h"
#include "../math/Math.h"

#include <iostream>

void TrailEffect::update(float deltaTime)
{
	// Spawn
	if (canSpawn) {
		currentSpawnTime += deltaTime;
		if (currentSpawnTime >= spawnStep) {
			// Calculate Direction
			float randomDirection = Math::getRandomFloat(-15, 15);
			float newDirx = cosf(Math::degToRad(randomDirection)) * direction.x - (sinf(Math::degToRad(randomDirection)) * direction.y);
			float newDiry = sinf(Math::degToRad(randomDirection)) * direction.x + (cosf(Math::degToRad(randomDirection)) * direction.y);
			Vector2 newDir = Vector2(newDirx, newDiry);
			particles.push_back(new Particle(this->position, newDir, Vector3(0.6f, 0.6f, 0.0f), 80.0f, 0.5f, 1.0f));
		}		
	}

	// Check if particle is done
	for (unsigned i = particles.size(); i-- > 0;) {
		if (particles[i]->isDone())
			particles.erase(particles.begin() + i);
	}

	// Update Particles
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->update(deltaTime);
	}
}

void TrailEffect::draw()
{
	// Draw Particles
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->draw();
	}
}
