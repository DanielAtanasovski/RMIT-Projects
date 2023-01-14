#pragma once
#include "../math/Vector3.h"
#include <string>

class Entity
{
public:
	Entity() {};
	Entity(Vector3 position, float rotation = 0.0f);
	virtual void draw() {};
	virtual void update(float deltaTime) {};
	virtual void setMaterial() {};
	Vector3 getPosition() { return position; };
	std::string getTag() { return tag; };
	bool getDead() { return isDead; }

protected:
	Vector3 position = Vector3();
	float rotation = 0.0f;
	std::string tag = "";
	bool isDead = false;
};

