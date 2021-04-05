#include "Vector.h"

Vector::Vector()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector::Vector(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector::~Vector()
{
}

void Vector::zero()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector Vector::operator+(const Vector& other)
{
	return Vector(this->x + other.x, this->y + other.y);
}

Vector Vector::operator-(const Vector& other)
{
	return Vector(this->x - other.x, this->y - other.y);
}
