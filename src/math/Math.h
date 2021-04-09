#pragma once
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class Math
{
public:
	static float degToRad(float degree);
	static float clamp(float value, float min, float max);
	static float maxValue(float value1, float value2);
	static int getRandomInt(int min, int max);
	static float getRandomFloat(float min, float max);
	static bool getRandomBool();
};

