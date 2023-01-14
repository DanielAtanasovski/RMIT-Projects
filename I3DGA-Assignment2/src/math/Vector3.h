#pragma once
#include <iostream>

/// <summary>
/// Created by Daniel Atanasovski
/// </summary>

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();
	void zero();
	float magnitude();
	float distanceTo(Vector3 other);
	Vector3 normalised();
	static Vector3 lerp(Vector3 from, Vector3 towards, float ratio);
	Vector3 operator+(const Vector3& other);
	Vector3 operator-(const Vector3& other);
	Vector3 operator-() const;
	Vector3 operator+=(const Vector3& other);
	Vector3 operator-=(const Vector3& other);
	Vector3 operator*(const float scalar);
	Vector3 operator*(const Vector3& other);
	friend std::ostream& operator<<(std::ostream& out, const Vector3& vector);
	float x, y, z = 0.0f;

};

