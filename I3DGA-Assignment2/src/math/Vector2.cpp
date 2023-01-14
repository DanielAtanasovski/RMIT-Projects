#include "Vector2.h"
#include <math.h>
#include "Math.h"

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

Vector2 Vector2::lerp(Vector2 from, Vector2 towards, float ratio)
{
	return Vector2(Math::lerp(from.x, from.x, ratio), Math::lerp(from.y, from.y, ratio));
}

Vector2 Vector2::operator+(const Vector2& other)
{
	return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator+=(const Vector2& other)
{
	return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other)
{
	return Vector2(this->x - other.x, this->y - other.y);
}

Vector2 Vector2::operator-()
{
	return Vector2(-this->x, -this->y);
}

Vector2 Vector2::operator*(const float scalar) {
	return Vector2(this->x * scalar, this->y * scalar);
}

Vector2 Vector2::operator*=(const float scalar) {
	return Vector2(this->x * scalar, this->y * scalar);
}

std::ostream& operator<<(std::ostream& out, const Vector2& vector)
{
	return out << vector.x << "," << vector.y;
}

float Vector2::dot(const Vector2& other)
{
	return (float)(x * other.x + y * other.y);
}

float Vector2::distanceTo(Vector2 other) {
	float dx = pow((this->x - other.x), 2);
	float dy = pow((this->y - other.y), 2);
	return (float)sqrt(dx + dy);
}


