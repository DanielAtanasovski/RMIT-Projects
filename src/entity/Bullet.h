#pragma once
#include "../physics/CollidableEntity.h"
#include "../Game.h"
class Bullet : public CollidableEntity
{
public:
	Bullet(Game& game, Vector2 position, Vector2 direction) : game(game), CollidableEntity(position, 0) { tag = "Bullet"; this->direction = direction; }
	~Bullet() {};
	void update(float deltaTime) override;
	void draw() override;
	void onCollide(CollidableEntity& other) override;


private:
	Game& game;
	const float SIZE = 10.0f;
	const float SPEED = 120.0f;
	const Vector3 colour = Vector3(1.0f, 0.0f, 0.0f);

};

