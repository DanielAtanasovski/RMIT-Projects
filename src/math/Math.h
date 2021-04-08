#pragma once
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class Math
{
public:
	static float degToRad(float degree);
	static float clamp(float value, float min, float max);
};

