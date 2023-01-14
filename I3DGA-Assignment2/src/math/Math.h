#pragma once
//#ifndef M_PI
//#define M_PI 3.14159265358979323846
//#endif

#include <vector>
#include <random>
#include "Vector3.h"

const double M_PI = 3.14159265358979323846;

class Math
{
public:
	static float degToRad(float degree);
	static float clamp(float value, float min, float max);
	static float maxValue(float value1, float value2);
	static int getRandomInt(int min, int max);
	static float getRandomFloat(float min, float max);
	static bool getRandomBool();
	static bool vectorContains(std::vector<std::pair<int,int>> vector, std::pair<int,int> compare);
	static float lerp(float current, float towards, float ratio);
	static float difference(float a, float b);
	static Vector3 crossProduct(Vector3 a, Vector3 b);
private:
	static std::random_device randomDevice;
	static std::mt19937 generator;
};

