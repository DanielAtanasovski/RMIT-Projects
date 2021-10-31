#include "BoxCollider.h"

#include "SphereCollider.h"

bool BoxCollider::intersects(SphereCollider const& other) const
{
	float distance = other.getRadius() * other.getRadius();

	// x
	if (other.getPosition().x < getMinCorner().x) distance -= squared(other.getPosition().x - getMinCorner().x);
	else if (other.getPosition().x > getMaxCorner().x) distance -= squared(other.getPosition().x - getMaxCorner().x);
	// y
	if (other.getPosition().y < getMinCorner().y) distance -= squared(other.getPosition().y - getMinCorner().y);
	else if (other.getPosition().y > getMaxCorner().y) distance -= squared(other.getPosition().y - getMaxCorner().y);
	// z
	if (other.getPosition().z < getMinCorner().z) distance -= squared(other.getPosition().z - getMinCorner().z);
	else if (other.getPosition().z > getMaxCorner().z) distance -= squared(other.getPosition().z - getMaxCorner().z);

	return distance > 0;
}

bool BoxCollider::intersects(BoxCollider const& other) const
{
	return (
		(getMinCorner().x <= other.getMaxCorner().x && getMaxCorner().x >= other.getMinCorner().x) &&
		(getMinCorner().y <= other.getMaxCorner().y && getMaxCorner().y >= other.getMinCorner().y) &&
		(getMinCorner().z <= other.getMaxCorner().z && getMaxCorner().z >= other.getMinCorner().z)
		);
}
