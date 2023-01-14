#include "SphereCollider.h"

#include <math.h>
#include "BoxCollider.h"

bool SphereCollider::intersects(SphereCollider const& other) const
{
	float distance = sqrtf(
		(_position.x - other.getPosition().x) * (_position.x - other.getPosition().x) +
		(_position.y - other.getPosition().y) * (_position.y - other.getPosition().y) +
		(_position.z - other.getPosition().z) * (_position.z - other.getPosition().z)
	);
	return distance < (_radius + other.getRadius());
}

bool SphereCollider::intersects(BoxCollider const& other) const
{
	float distance = _radius * _radius;

	// x
	if (_position.x < other.getMinCorner().x) distance -= squared(_position.x - other.getMinCorner().x);
	else if (_position.x > other.getMaxCorner().x) distance -= squared(_position.x - other.getMaxCorner().x);
	// y
	if (_position.y < other.getMinCorner().y) distance -= squared(_position.y - other.getMinCorner().y);
	else if (_position.y > other.getMaxCorner().y) distance -= squared(_position.y- other.getMaxCorner().y);
	// z
	if (_position.z < other.getMinCorner().z) distance -= squared(_position.z - other.getMinCorner().z);
	else if (_position.z > other.getMaxCorner().z) distance -= squared(_position.z - other.getMaxCorner().z);

	return distance > 0;
}
