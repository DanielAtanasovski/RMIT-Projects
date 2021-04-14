#include "Math.h"
#include <chrono>
#include <random>

std::random_device Math::randomDevice;
std::mt19937 Math::generator(Math::randomDevice());

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
	std::uniform_int_distribution<int> uni(min, max);

	return uni(generator);
}

float Math::getRandomFloat(float min, float max) {
	std::uniform_real_distribution<float> uni(min, max);

	return uni(generator);
}

bool Math::getRandomBool() {
	std::uniform_real_distribution<float> uni(-1, 1);

	float value = uni(generator);
	if (value >= 0)
		return true;
	

	return false;
}

bool Math::vectorContains(std::vector<std::pair<int, int>> vector, std::pair<int, int> compare)
{
	for (size_t i = 0; i < vector.size(); i++)
	{
		if (
			(vector[i].first == compare.first && vector[i].second == compare.second) ||
			(vector[i].first == compare.second && vector[i].second == compare.first)
			)
			return true;
	}
	return false;
}
