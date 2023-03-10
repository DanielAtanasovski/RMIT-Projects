#pragma once
#include "../physics/CollidableEntity.h"
#include "../math/Math.h"
#include <vector>
#include "../Game.h"
#include "../effects/ExplosionEffect.h"

class Asteroid : public CollidableEntity
{
public:
	Asteroid(Game& game, Vector2 position, bool canSpawnAsteroid = true);
	Asteroid(Game& game, Vector2 position, float size, bool canSpawnAsteroid = true);
	~Asteroid() {};
	void generateAsteroid();
	void generateAsteroid(float size);
	void drawAsteroid();
	void draw() override;
	void update(float deltaTime) override;
	void onCollide(CollidableEntity& other) override;
	void setDirection(Vector2 direction);

	// Useful values to be seen everywhere
	static constexpr float MAX_SIZE = 14.0f; // Used by Arena to determine safe spawn area

private:
	const int MAX_POINTS = 14; // Amount of points used to draw asteroid
	 // Biggest size
	const float MIN_SIZE = 8.0f; // smallest size
	const float MAX_SIZE_OFFSET = 2.0f; // max difference between each point
	const float MIN_SIZE_OFFSET = -1.5f;
	const float MIN_SPEED = 20.0f;
	const float MAX_SPEED = 40.0f;
	const float MIN_ROTATION_SPEED = 10.0f;
	const float MAX_ROTATION_SPEED = 25.0f;

	const Vector3 FILL_COLOUR = Vector3(0.4f, 0.4f, 0.4f);
	const Vector3 OUTLINE_COLOUR = Vector3(0.8f, 0.8f, 0.8f);

	const bool ROTATE_CLOCKWISE = Math::getRandomBool();

	const float SPEED = Math::getRandomFloat(MIN_SPEED, MAX_SPEED);
	const float ROTATION_SPEED = Math::getRandomFloat(MIN_ROTATION_SPEED, MAX_ROTATION_SPEED);

	float health = 1;
	float size = Math::getRandomFloat(MIN_SIZE, MAX_SIZE);
	bool canSpawnAsteroid = true;
	bool isDestroyed = false;
	ExplosionEffect* explosionEffect;
	std::vector<Vector2> drawPoints = std::vector<Vector2>();
	Game& game;
};