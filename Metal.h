#pragma once

#include "rtintro.h"
#include "IMaterial.h"
#include "vec3.h"

class Metal : public IMaterial {
public:
	Metal(const color& c, double fuzz) : m_albedo(c), m_fuzz(fuzz) {
	}

	virtual bool scatter(const ray& rayIn, const HitRecord& hit, color& attenuation, ray& scattered) const {
		auto reflected = reflect(normalize(rayIn.direction), hit.normal);
		scattered = ray(hit.p, reflected + m_fuzz * randomInUnitSphere());
		attenuation = m_albedo;

		return dot(scattered.direction, hit.normal) > 0.0;
	}

private:
	color m_albedo;	
	double m_fuzz;
};
