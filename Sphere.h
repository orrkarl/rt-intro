#pragma once

#include "IHittable.h"
#include "ray.h"

class Sphere : public IHittable {
public:
	Sphere(const point3& center, double radius);

	bool hit(const ray& r, TBoundaries bounds, HitRecord& record) const override;

	point3 center() const;
	double radius() const;

private:
	point3 m_center;
	double m_radius;
};

