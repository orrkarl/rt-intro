#pragma once

#include "rtintro.h"
#include "vec3.h"

inline double fresnelFactor(double cos, double eta1, double eta2) {
	// Using schlick's approximation
	auto r0 = (eta1 - eta2) / (eta1 + eta2);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow(1 - cos, 5);
}

inline vec3 snellRefract(const vec3& r, const vec3& normal, double eta1, double eta2) {
	auto cosTheta = dot(-r, normal);
	auto snellRatio = eta1 / eta2;
	
	auto sinTheta = std::sqrt(1 - cosTheta * cosTheta);
	if (snellRatio * sinTheta > 1.0) {
		return reflect(r, normal);
	}

	if (nextRandomDouble() < fresnelFactor(cosTheta, eta1, eta2)) {
		return reflect(r, normal);
	}

	auto outParallel = snellRatio * (r + cosTheta * normal);
	auto outPerp = -std::sqrt(1.0 - outParallel.lengthSquared()) * normal;
	return outPerp + outParallel;
}

