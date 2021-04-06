#pragma once

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
	Vector3 operator+(const Vector3& other);
	Vector3 operator-(const Vector3& other);
	float x, y, z = 0.0f;

};

