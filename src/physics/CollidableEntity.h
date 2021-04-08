#pragma once
#include "../entity/Entity.h"

class CollidableEntity: public Entity
{
public:
	float getCollisionRadius() { return collisionRadius; }

private:
	const bool DEBUG_DRAW = false;
	float collisionRadius = 0.0f;
};

