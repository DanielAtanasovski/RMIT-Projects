#pragma once
#include "../entity/Entity.h"
#include "../math/Vector3.h"

class CollidableEntity: public Entity
{
public:
	CollidableEntity(Vector2 position, float rotation) : Entity(position, rotation) {}
	float getCollisionRadius() { return collisionRadius; }
	void drawDebugCollisionCircle();
	void draw() override { if (DEBUG_DRAW_CIRCLE) drawDebugCollisionCircle(); }

protected:
	float collisionRadius = 0.0f;
private:
	const bool DEBUG_DRAW_CIRCLE = true;
	const Vector3 DEBUG_COLOUR = Vector3(0.0f, 1.0f, 0.0f);
	const float DEBUG_CIRCLE_MAX_STEPS = 32;
};

