#pragma once

#include "world/Arena.h"
#include "entity/Player.h"
#include <vector>

class Arena;
class Player;

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
	void deleteCollidableEntity(CollidableEntity* entity);
	void increaseScore(float scoreIncrease) { score += scoreIncrease; };
	bool isPointSafe(Vector2 point, float radius); // check if spaw is safe for spawn
	void drawString(float x, float y, std::string str);
	float getStringSize(std::string str);
	float getWidth() { return width; };
	float getHeight() { return height; };
	Vector2 worldToScreenCoordinate(Vector2 point);
	Player& getPlayer() { return *player; };
	Arena& getArena() { return *arena; }

	// consts
	const bool FULLSCREEN = false;
	const float WORLD_UNIT_MIN = -120.0f;
	const float WORLD_UNIT_MAX = 120.0f;
	const float WORLD_UNIT_DEPTH = 1.0f;

private:
	float width = 0;
	float height = 0;
	int gameState = 0;
	Player* player = nullptr;
	Arena* arena = nullptr;
	float lastElapsedTime = 0.0f;
	std::vector<CollidableEntity*> collidableEntities = std::vector<CollidableEntity*>();
	std::vector<int> queueDeleteList = std::vector<int>();
	int asteroidsCount = 0;
	int score = 0;
	float time = 0;

	// consts
	const std::string END_MESSAGE = "Game Over. Press any key to play again...";
	const std::string START_MESSAGE = "Press any key to start...";
	const Vector2 PLAYER_START_POSITION = Vector2(-70, -70);
	const float PLAYER_START_ROTATION = 45;

	// States
	const int STATE_START = 0;
	const int STATE_GAME = 1;
	const int STATE_END = 2;
	const float STATE_END_TIMEOUT = 0.5f; // so it automatically doesnt restart

	void restart();
	bool playerOutOfBounds(); // Player and Arena
	void CollisionCheckCollidables(); // Asteroids with eachother and player
	void queueCollidableDelete(int index);
	void runQueueDelete();
	bool isOutsideWorld(CollidableEntity& entity); // delete items that no longer relevant
};