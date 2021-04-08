#include "Math.h"

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
