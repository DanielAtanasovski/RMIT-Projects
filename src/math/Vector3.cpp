#include "Vector3.h"
#include "Math.h"

Vector3::Vector3()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3()
{
}

void Vector3::zero()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3 Vector3::operator+(const Vector3& other)
{
	return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other)
{
	return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3 Vector3::operator+=(const Vector3& other)
{
	return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3 Vector3::operator*(const float scalar) {
	return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
}

Vector3 Vector3::lerp(Vector3 from, Vector3 towards, float ratio) {
	return Vector3(Math::lerp(from.x, towards.x, ratio), Math::lerp(from.y, towards.y, ratio), Math::lerp(from.z, towards.z, ratio));
}