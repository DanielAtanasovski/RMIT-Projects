#pragma once
#include "../math/Vector2.h"
#include "../math/Vector3.h"
#include "../physics/CollidableEntity.h"

//#include "../effects/TrailEffect.h"
#include "Arena.h"
#include "../Game.h"
#include "../math/Math.h"
#include "Bullet.h"
#include "Camera.h"

#include "tiny_obj_loader.h"

class Game;
class Camera;
class Bullet;

class Player : public CollidableEntity
{
public:
	Player(Game& game, Vector3 position, float rotation);
	~Player() { /*delete trailEffect;*/ };
	void draw() override;
	void update(float deltaTime) override;
	virtual void onCollide(CollidableEntity& other) {}
	void setDead(bool dead) { this->dead = dead; }
	void setRotation(float rotation) { this->rotation = rotation; }
	void setPosition(Vector3 position) { this->position = position; }
	void restart() { bullets.clear(); }
	const std::vector<Bullet*>& getBullets() const { return bullets; };

private:
	void shoot(float deltaTime);
	void bulletsCheck(float deltaTime);
	void bulletsDraw();
	void bulletsUpdate(float deltaTime);
	void drawShip();
	bool loadModel();
	void setBodyMaterial();
	void setWindowMaterial();

	Vector2 inputVector;
	float velocity = 0.0f;
	//TrailEffect3D* trailEffect;
	bool isMoving = false;
	Game& game;
	
	// Shooting
	std::vector<Bullet*> bullets = std::vector<Bullet*>();
	bool canShoot = true;
	float currentFireRate = 0.0f;
	bool dead = false;
	float rotAmount = 0;
	float rotSpeed = 50.0f;

	// Camera
	float distFromCamera = 6.0f;
	const float MAX_DISTANCE_FROM_CAMERA = 20.0f;
	const float MIN_DISTANCE_FROM_CAMERA = 0.0f;
	const float DISTANCE_FROM_CAMERA_STEP = 1.0f;

	// Model
	std::string SHIP_MODEL_PATH = "../resources/modified_ship.obj";
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::material_t> materials;
	std::vector<tinyobj::shape_t> shapes;
	std::string warn;
	std::string err;

	const std::string SHAPE_WINDOW_NAME = "Window_Window_Mesh";
	const std::string SHAPE_BODY_NAME = "Body_Body_Mesh";

	// Stats
	const float FIRE_RATE = 0.2f;

};

