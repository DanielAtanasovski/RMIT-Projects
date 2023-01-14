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

float Vector3::magnitude()
{
	return (float)sqrt((x * x) + (y * y) + (z * z));
}

Vector3 Vector3::normalised()
{
	return Vector3(x / magnitude(), y / magnitude(), z / magnitude());
}

Vector3 Vector3::operator+(const Vector3& other)
{
	return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other)
{
	return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-this->x, -this->y, -this->z);
}

Vector3 Vector3::operator+=(const Vector3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Vector3 Vector3::operator-=(const Vector3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Vector3 Vector3::operator*(const float scalar) {
	return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
}

Vector3 Vector3::operator*(const Vector3& other) {
	return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
}

std::ostream& operator<<(std::ostream& out, const Vector3& vector)
{
	return out << "(" << vector.x << "," << vector.y << "," << vector.z << ")";
}

Vector3 Vector3::lerp(Vector3 from, Vector3 towards, float ratio) {
	return Vector3(Math::lerp(from.x, towards.x, ratio), Math::lerp(from.y, towards.y, ratio), Math::lerp(from.z, towards.z, ratio));
}

float Vector3::distanceTo(Vector3 other) {
	float dx = pow((this->x - other.x), 2);
	float dy = pow((this->y - other.y), 2);
	float dz = pow((this->z - other.z), 2);
	return (float)sqrt(dx + dy + dz);
}