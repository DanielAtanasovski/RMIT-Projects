#pragma once

#include "world/Arena.h"
#include "entity/Player.h"
#include <vector>

class Game
{
public:
	Game();
	~Game() {};
	void init();
	void draw();
	void update();
	void onReshape(int width, int height);
	void createCollidableEntity(CollidableEntity* entity);
	bool isPointSafe(Vector2 point, float radius); // check if spaw is safe for spawn

	// consts
	const bool FULLSCREEN = false;
	const float WORLD_UNIT_MIN = -160.0f;
	const float WORLD_UNIT_MAX = 160.0f;
	const float WORLD_UNIT_DEPTH = 1.0f;

private:
	Player* player = nullptr;
	Arena* arena = nullptr;
	float lastElapsedTime = 0.0f;
	std::vector<CollidableEntity*> collidableEntities = std::vector<CollidableEntity*>();
	std::vector<int> queueDeleteList = std::vector<int>();
	int asteroidsCount = 0;

	void restart();
	
	bool playerOutOfBounds(); // Player and Arena
	void CollisionCheckCollidables(); // Asteroids with eachother and player
	void queueCollidableDelete(int index);
	void runQueueDelete();
	bool isOutsideWorld(CollidableEntity& entity); // delete items that no longer relevant

};