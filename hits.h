#pragma once

#include "ray3.h"
#include "vec3.h"

double intersection(const vec3& center, double radius, const ray3& r) {
	auto delta = r.origin - center;

	const auto a = r.direction.lengthSquared();
	const auto b = 2.0 * dot(delta, r.direction);
	const auto c = delta.lengthSquared() - radius * radius;

	const auto discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		return -1.0;
	}

	return (-b - std::sqrt(discriminant)) / (2.0 * a);
}

