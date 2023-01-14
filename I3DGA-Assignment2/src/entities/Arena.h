#pragma once
#include "Player.h"
#include "../math/Vector2.h"
#include "../math/Math.h"
#include "Asteroid.h"
#include <random>

/// <summary>
/// Responsible for the arena and spawning of Asteroids
/// </summary>

class Game;
class Asteroid;

class Arena
{

public:
	Arena(Game& game) : game(game) {};
	~Arena() {};
	void draw();
	void update(float deltaTime);
	void restart() { asteroids.clear(); };
	const std::vector<Asteroid*>& getAsteroids() const { return asteroids; };

private:
	// Consts
	const float WARNING_DISTANCE = 30.0f;
	const float ARENA_SIZE = 200.0f;
	const float ASTEROID_SPAWN_OFFSET = 50.0f;
	const int MAX_WAVE_SIZE = 5;
	const int MAX_ASTEROIDS = 8;
	const float TIME_BETWEEN_WAVES = 5.0f;

	int waveSize = 2;
	float currentWaveTime = 0;
	std::vector<Asteroid*> asteroids = std::vector<Asteroid*>();

	const Vector3 X_DIRECTION = Vector3(1, 0, 0);
	const Vector3 Y_DIRECTION = Vector3(0, 1, 0);
	const Vector3 Z_DIRECTION = Vector3(0, 0, 1);
	const Vector3 X_NEG_DIRECTION = Vector3(-1, 0, 0);
	const Vector3 Y_NEG_DIRECTION = Vector3(0, -1, 0);
	const Vector3 Z_NEG_DIRECTION = Vector3(0, 0, -1);

	const Vector3 DEFAULT_COLOR = Vector3(0.4f, 0.4f, 0.4f);
	const Vector3 PLAYER_CLOSE_COLOR = Vector3(0.6f, 0.0f, 0.0f);

	// Reference
	Game& game;

	void drawArena();
	void drawWallSegments(float size);
	bool playerCloseToWall(Vector3 direction, float wallValue);
	void spawnAsteroid(Vector3 position, Vector3 direction);
	Vector3 getRandomAsteroidPosition();
	void spawnWave();
	void asteroidsCheck(float deltaTime);
	void asteroidsDraw();
	void asteroidsUpdate(float deltaTime);
};


