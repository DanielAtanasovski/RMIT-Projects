#pragma once
#include "../math/Vector2.h"
#include <string>
class Entity
{
public:
	Entity() {};
	Entity(Vector2 position, float rotation = 0.0f);
	virtual void draw() {};
	virtual void update(float deltaTime) {};
	Vector2 getPosition() { return position; };
	std::string getTag() { return tag; };
	
protected:
	Vector2 position = Vector2();
	float rotation = 0.0f;
	std::string tag = "";
};

