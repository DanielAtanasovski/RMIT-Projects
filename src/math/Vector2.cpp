#include "Vector2.h"
#include <math.h>

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

float Vector2::magnitude()
{
	return (float)sqrt((x*x) + (y*y));
}

Vector2 Vector2::normalised()
{
	return Vector2(x / magnitude(), y / magnitude());
}

Vector2 Vector2::operator+(const Vector2& other)
{
	return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other)
{
	return Vector2(this->x - other.x, this->y - other.y);
}

float Vector2::distanceTo(Vector2 other) {
	float dx = pow((this->x - other.x), 2);
	float dy = pow((this->y - other.y), 2);
	return (float)sqrt(dx + dy);
}
