#pragma once

#include "entities/Arena.h"
#include "entities/Player.h"
#include "entities/Camera.h"
#include <vector>

#include "stb_image.h"

class Arena;
class Player;
class Camera;
class Bullet;

class Game
{
public:
	Game();
	~Game() {};
	void init();
	void draw();
	void update();
	void onReshape(int width, int height);
	void checkCollidables();
	void increaseScore(float scoreIncrease) { score += scoreIncrease; }
	bool isPointSafe(Vector3 point, float radius); // check if spaw is safe for spawn
	void drawString(float x, float y, std::string str);
	float getStringSize(std::string str);
	float getWidth() { return width; }
	float getHeight() { return height; }
	Vector2 worldToScreenCoordinate(Vector2 point);
	Player& getPlayer() { return *player; }
	Arena& getArena() { return *arena; }
	Camera& getCamera() { return *camera; }
	void killPlayer();

	// Textures
	uint32_t getShipTexture() { return shipTexture; };

	// consts
	const bool FULLSCREEN = false;
	const float WORLD_UNIT_MIN = -100.0f;
	const float WORLD_UNIT_MAX = 100.0f;

private:
	float light_position1[4] = { 0.0, 120.0, 0.0, 0.0 };
	float ambient_light1[4] = { 0.3, 0.3, 0.0, 1.0 };
	float specular_light1[4] = { 0.1, 0.1, 0.1, 1.0 };
	float light_direction1[4] = { 0, -1, 0, 0 };

	float light_position2[4] = { 100.0, 0.0, 0.0, 0.0 };
	float ambient_light2[4] = { 0, 0, 0, 1 };
	float specular_light2[4] = { 1.0, 0.0, 0.0, 1 };
	float light_direction2[4] = { -1, 0, 0, 0 };


	float width = 0;
	float height = 0;
	int gameState = 0;
	Player* player = nullptr;
	Arena* arena = nullptr;
	Camera* camera = nullptr;
	float lastElapsedTime = 0.0f;
	std::vector<CollidableEntity*> collidableEntities = std::vector<CollidableEntity*>();
	std::vector<int> queueDeleteList = std::vector<int>();
	int asteroidsCount = 0;
	int score = 0;
	float time = 0;

	uint32_t shipTexture = 0;

	// consts
	const std::string END_MESSAGE = "Game Over. Press any key to play again...";
	const std::string START_MESSAGE = "Press any key to start...";
	const Vector3 PLAYER_START_POSITION = Vector3(0, 0, 0);
	const float PLAYER_START_ROTATION = 0;

	// States
	const int STATE_START = 0;
	const int STATE_GAME = 1;
	const int STATE_END = 2;
	const float STATE_END_TIMEOUT = 0.5f; // so it automatically doesnt restart
	float currentTimeout = 0.0f;

	void restart();
	bool playerOutOfBounds(); // Player and Arena
	void CollisionCheckCollidables(); // Asteroids with eachother and player
	void queueCollidableDelete(int index);
	void runQueueDelete();
	bool isOutsideWorld(CollidableEntity& entity); // delete items that no longer relevant
	void updateCamera();
	void loadTextures();
	uint32_t loadTexture(const char* filename);
};