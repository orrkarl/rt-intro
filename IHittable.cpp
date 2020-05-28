#include "IHittable.h"

HitRecord::HitRecord(const point3& p, const vec3& outwardsNormal, const vec3& rayDirection, double t)
	: p(p), frontFace(dot(outwardsNormal, rayDirection) < 0.0), normal(frontFace ? outwardsNormal : -outwardsNormal), t(t) {
}

bool isInBounds(const TBoundaries& bounds, double t) {
	return bounds.min < t && t < bounds.max;
}
