#pragma once
#include "../physics/CollidableEntity.h"
#include "../Game.h"

class Game;

class Bullet : public CollidableEntity
{
public:
	Bullet(Game& game, Vector3 position, Vector3 direction) : game(game), CollidableEntity(position, 0) {
		tag = "Bullet";
		this->direction = direction;
		collisionRadius = SIZE;
	}
	~Bullet() {};
	void update(float deltaTime) override;
	void draw() override;
	void onCollide(CollidableEntity& other) override;


private:
	Game& game;
	const float SIZE = 10.0f;
	const float SPEED = 120.0f;
	const Vector3 colour = Vector3(1.0f, 0.0f, 0.0f);

	const float mat_ambient[4] = { 1.0, 0, 0, 1.0 };
	const float mat_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	const float mat_specular[4] = { 1.0, 0.1, 0.1, 1.0 };
	const float mat_shininess[1] = { 10.0 };

};

