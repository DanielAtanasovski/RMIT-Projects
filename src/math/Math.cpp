#include "Math.h"
#include <random>

float Math::degToRad(float degree) {
	return degree * (float(M_PI) / 180);
}

float Math::clamp(float value, float min, float max)
{
	if (value <= max && value >= min)
		return value;
	else if (value > max)
		return max;
	else
		return min;
}

float Math::maxValue(float value1, float value2)
{
	if (value1 >= value2)
		return value1;
	return value2;
}

int Math::getRandomInt(int min, int max)
{
	std::random_device randomDevice;
	std::mt19937 rng(randomDevice());
	std::uniform_int_distribution<int> uni(min, max);

	return uni(rng);
}

float Math::getRandomFloat(float min, float max) {
	std::random_device randomDevice;
	std::mt19937 rng(randomDevice());
	std::uniform_real_distribution<float> uni(min, max);

	return uni(rng);
}
