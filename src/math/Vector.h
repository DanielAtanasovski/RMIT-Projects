#pragma once

/// <summary>
/// Created by Daniel Atanasovski
/// </summary>

class Vector
{
public:
	Vector();
	Vector(float x, float y);
	~Vector();
	void zero();
	Vector operator+(const Vector& other);
	Vector operator-(const Vector& other);
	float x, y = 0.0f;
	
};

