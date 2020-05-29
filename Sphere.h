#pragma once

#include <memory>

#include "IHittable.h"
#include "ray.h"

class IMaterial;

class Sphere : public IHittable {
public:
	Sphere(const point3& center, double radius, std::shared_ptr<IMaterial> material);

	bool hit(const ray& r, TBoundaries bounds, HitRecord& record) const override;

	point3 center() const;
	double radius() const;
	std::shared_ptr<IMaterial> material() const;

private:
	point3 m_center;
	double m_radius;
	std::shared_ptr<IMaterial> m_materialPtr;
};

