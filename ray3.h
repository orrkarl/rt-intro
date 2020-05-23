#pragma once

#include "vec3.h"

class ray3 {
public:
	ray3() = default;

	ray3(const point3& origin, const vec3& dir)
		: origin(origin), direction(dir) {
	}

	point3 at(double t) const {
		return origin + t * direction;
	}

	point3 operator()(double t) const {
		return at(t);
	}

public:
	point3 origin;
	vec3 direction;
};

