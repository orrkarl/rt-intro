#pragma once

#include "ray3.h"

struct TBoundaries {
	double min;
	double max;
};

struct HitRecord {
	point3 p;
	vec3 normal;
	double t;
};

class IHittable {
public:
	virtual bool hit(const ray3& ray, const TBoundaries& bounds, HitRecord& record) const = 0;
};

bool isInBounds(const TBoundaries& bounds, double t); 
