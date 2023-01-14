#pragma once

#include "Collider.h"
#include <glm/ext/vector_float2.hpp>

class BoxCollider : public Collider {
public:
	BoxCollider(glm::vec3 size) {
		_width = size.x;
		_height = size.y;
		_depth = size.z;
	};

	glm::vec3 getHalfExtents() const { return glm::vec3(_width / 2, _height / 2, _depth / 2); };
	// Inherited via Collider
	virtual bool intersects(Collider const& other) const {
		return other.intersects(*this);
	};

	glm::vec3 getMinCorner() const {
		return glm::vec3(
			getPosition().x - getHalfExtents().x,
			getPosition().y - getHalfExtents().y,
			getPosition().z - getHalfExtents().z);
	};

	glm::vec3 getMaxCorner() const {
		return glm::vec3(
			getPosition().x + getHalfExtents().x,
			getPosition().y + getHalfExtents().y,
			getPosition().z + getHalfExtents().z);
	};

protected:
	float _width, _height, _depth;

	inline float squared(float v) const { return v * v; }

	// Inherited via Collider
	virtual bool intersects(SphereCollider const& other) const;

	virtual bool intersects(BoxCollider const& other) const;

};