#include "Vector2.h"

Vector2::Vector2()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::~Vector2()
{
}

void Vector2::zero()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2 Vector2::operator+(const Vector2& other)
{
	return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other)
{
	return Vector2(this->x - other.x, this->y - other.y);
}
