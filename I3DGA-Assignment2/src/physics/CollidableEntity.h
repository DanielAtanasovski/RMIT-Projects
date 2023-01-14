#pragma once
#include "../entities/Entity.h"
#include "../math/Vector3.h"

class CollidableEntity : public Entity
{
public:
	CollidableEntity(Vector3 position, float rotation) : Entity(position, rotation) {}
	float getCollisionRadius() { return collisionRadius; }
	void drawDebugCollisionCircle();
	Vector3 getDirection() { return this->velocity.normalised(); }
	//void setDirection(Vector2 direction) { this->direction = direction; }
	Vector3 getVelocity() { return velocity; }
	void setVelocity(Vector3 velocity) { this->velocity = velocity; }
	bool getInsideArena() { return insideArena; };
	void setInsideArena(bool value) { insideArena = value; }
	virtual void onCollide(CollidableEntity& other) {};
	bool isEnabled() { return enabled; }

protected:
	float collisionRadius = 0.0f;
	Vector3 direction = Vector3(0, 0, 0);
	Vector3 velocity = Vector3(0, 0, 0);
	bool enabled = true;
private:
	const Vector3 DEBUG_COLOUR = Vector3(0.0f, 1.0f, 0.0f);
	const float DEBUG_CIRCLE_MAX_STEPS = 32;
	bool insideArena = false;
};

