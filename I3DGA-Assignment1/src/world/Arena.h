#pragma once
#include "../entity/Player.h"
#include "../math/Vector2.h"
#include "../math/Math.h"
#include <random>

/// <summary>
/// Responsible for the arena and spawning of Asteroids
/// </summary>

class Game;

class Arena
{

public:
	Arena(Game& game) : game(game) {};
	~Arena() {};
	void draw();
	void update(float deltaTime);
	void restart();

	// Consts
	const float WIDTH = 198;
	const float HEIGHT = 198;

	// Walls
	const Vector2 TOP_LEFT_POINT = Vector2(-WIDTH / 2, HEIGHT / 2);
	const Vector2 BOTTOM_LEFT_POINT = Vector2(-WIDTH / 2, -HEIGHT / 2);
	const Vector2 TOP_RIGHT_POINT = Vector2(WIDTH / 2, HEIGHT / 2);
	const Vector2 BOTTOM_RIGHT_POINT = Vector2(WIDTH / 2, -HEIGHT / 2);

	const float ASTEROID_SPAWN_RADIUS_OFFSET = 20.0f;
	const float ASTEROID_SPAWN_RADIUS = (float)sqrt(pow(TOP_RIGHT_POINT.x, 2) + pow(TOP_RIGHT_POINT.y,2)) + ASTEROID_SPAWN_RADIUS_OFFSET; /*Math::maxValue(WIDTH / 2, HEIGHT / 2);*/

private:
	// Consts
	const float WARNING_DISTANCE = 30.0f;
	const float WAVE_SPAWN_TIME = 5.0f;
	const int WAVE_MAX_ASTEROIDS = 5;

	const Vector3 DEFAULT_LINE_COLOUR = Vector3(1.0f, 1.0f, 1.0f);
	const Vector3 WARNING_LINE_COLOUR = Vector3(1.0f, 0.0f, 0.0f);

	Vector3 topLineColour = Vector3(DEFAULT_LINE_COLOUR);
	Vector3 rightLineColour = Vector3(DEFAULT_LINE_COLOUR);
	Vector3 bottomLineColour = Vector3(DEFAULT_LINE_COLOUR);
	Vector3 leftLineColour = Vector3(DEFAULT_LINE_COLOUR);

	// Reference
	Game& game;

	float currentSpawnTime = 0.0f;
	int currentAsteroidsWave = 1;

	void spawnWave(int asteroids);
	void spawnerUpdate(float deltaTime);
	Vector2 getRandomSpawn();
	Vector2 getValidSpawnPoint();
	void lineCheck();
};


