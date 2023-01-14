#include "ExplosionEffect.h"
#include "../math/Math.h"
#include <iostream>

ExplosionEffect::ExplosionEffect(Vector2 position, Vector3 colour, int amountOfParticles)
{
	this->position = position;
	this->particlesColour = colour;
	this->amountOfParticles = amountOfParticles;

	std::cout << position.x << ", " << position.y << std::endl;
	for (size_t i = 0; i < amountOfParticles; i++)
	{
		float randomDirection = Math::getRandomFloat(0, 360);
		float randomSpeed = Math::getRandomFloat(PARTICLE_MIN_SPEED, PARTICLE_MAX_SPEED);
		float randomLifeTime = Math::getRandomFloat(PARTICLE_MIN_DURATION, PARTICLE_MAX_DURATION);
		float randomSize = Math::getRandomFloat(PARTICLE_MIN_SIZE, PARTICLE_MAX_SIZE);
		float x = cosf(Math::degToRad(randomDirection));
		float y = sinf(Math::degToRad(randomDirection));

		particles.push_back(new Particle(position, Vector2(x, y), colour, randomSpeed, randomLifeTime, randomSize));
	}
}

void ExplosionEffect::update(float deltaTime)
{
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

	if (particles.size() == 0)
		done = true;
}

void ExplosionEffect::draw()
{
	// Draw Particles
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->draw();
	}
}
