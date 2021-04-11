#pragma once
#include "../entity/Entity.h"
#include "../math/Vector3.h"

class CollidableEntity: public Entity
{
public:
	CollidableEntity(Vector2 position, float rotation) : Entity(position, rotation) {}
	float getCollisionRadius() { return collisionRadius; }
	void drawDebugCollisionCircle();

protected:
	float collisionRadius = 0.0f;
private:
	const Vector3 DEBUG_COLOUR = Vector3(0.0f, 1.0f, 0.0f);
	const float DEBUG_CIRCLE_MAX_STEPS = 32;
};

