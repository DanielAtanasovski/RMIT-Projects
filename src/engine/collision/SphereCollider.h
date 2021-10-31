#pragma once

#include "Collider.h"

class SphereCollider : public Collider {
public:
	SphereCollider(float radius) { _radius = radius; };

	// Inherited via Collider
	virtual bool intersects(Collider const& other) const {
		return other.intersects(*this);
	};

	float getRadius() const { return _radius; }
protected:
	float _radius;

	// Inherited via Collider
	virtual bool intersects(SphereCollider const& other) const;

	virtual bool intersects(BoxCollider const& other) const;

	inline float squared(float v) const { return v * v; }

};