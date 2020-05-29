#pragma once

#include "ray.h"

struct TBoundaries {
	double min;
	double max;
};

struct HitRecord {
	HitRecord() = default;
	HitRecord(const point3& p, const vec3& outwardsNormal, const vec3& rayDirection, double t);

	bool frontFace;
	point3 p;
	vec3 normal;
	double t;
};

class IHittable {
public:
	virtual bool hit(const ray& ray, TBoundaries bounds, HitRecord& record) const = 0;
};

bool isInBounds(const TBoundaries& bounds, double t); 
