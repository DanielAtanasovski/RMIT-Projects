#pragma once

#include <glm/vec3.hpp>

class GLMUtil {
public:
	static bool vecComparison(const glm::ivec3& a, const glm::ivec3& b)
	{
		return (a.x == b.x && a.y == b.y && a.z == b.z);
	}
};
