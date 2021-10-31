#pragma once
#include <glm/ext/vector_float3.hpp>

class SphereCollider;
class BoxCollider;

class Collider {
public:
	virtual bool intersects(Collider other) = 0;

	glm::vec3 getPosition() const { return _position; }
	glm::vec3 getDirection() const { return _direction; }

protected:
	virtual bool intersects(SphereCollider const& other) const = 0;
	virtual bool intersects(BoxCollider const& other) const = 0;

	friend class BoxCollider;
	friend class SphereCollider;

	glm::vec3 _position;
	glm::vec3 _direction;
	int _id;
};