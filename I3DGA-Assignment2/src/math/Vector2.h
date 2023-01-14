#pragma once
#include <iostream>

/// <summary>
/// Created by Daniel Atanasovski
/// </summary>

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();
	void zero();
	float magnitude();
	float distanceTo(Vector2 other);
	Vector2 normalised();
	Vector2 lerp(Vector2 from, Vector2 towards, float ratio);
	Vector2 operator+(const Vector2& other);
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2 operator-();
	Vector2 operator*(const float scalar);
	Vector2 operator*=(const float scalar);
	friend std::ostream& operator<<(std::ostream& out, const Vector2& vector);
	float dot(const Vector2& other);
	float x, y = 0.0f;
	
};

