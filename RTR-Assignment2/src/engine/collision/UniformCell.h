#pragma once

#include <vector>
#include "Collider.h"

class UniformCell {
public:
	UniformCell();

private:
	std::vector<Collider> _colliders;
};