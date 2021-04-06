#pragma once

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
	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	float x, y = 0.0f;
	
};

