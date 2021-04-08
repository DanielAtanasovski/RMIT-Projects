#pragma once
#include "../math/Vector2.h"
class Entity
{
public:
	Entity() {};
	Entity(Vector2 position, float rotation = 0.0f);
	virtual void draw() {};
	virtual void update(float deltaTime) {};
protected:
	Vector2 position = Vector2();
	float rotation = 0.0f;

};

