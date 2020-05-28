#include "Sphere.h"

Sphere::Sphere(const point3& center, double radius) 
	: m_center(center), m_radius(radius) {
	// Intentionally left empty
}

HitRecord makeHitRecord(const Sphere& c, const ray& r, double t) {
	const auto p = r.at(t);
	const auto normal = (p - c.center()) / c.radius();
	return {p, normal, r.direction, t};	
}

bool Sphere::hit(const ray& r, TBoundaries bounds, HitRecord& record) const {
	auto delta = r.origin - m_center;

	const auto a = r.direction.lengthSquared();
	const auto half_b = dot(delta, r.direction);
	const auto c = delta.lengthSquared() - m_radius * m_radius;

	const auto discriminant = half_b * half_b - a * c;

	if (discriminant < 0) {
		return false;
	}

	double t = (-half_b - std::sqrt(discriminant)) / a;
	if (isInBounds(bounds, t)) {
		record = makeHitRecord(*this, r, t);
		return true;
	}

	t = (-half_b + std::sqrt(discriminant)) / a;
	if (isInBounds(bounds, t)) {
		record = makeHitRecord(*this, r, t);
		return true;
	}

	return false;
}

point3 Sphere::center() const {
	return m_center;
}

double Sphere::radius() const {
	return m_radius;
}
