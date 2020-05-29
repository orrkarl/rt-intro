#pragma once

#include "rtintro.h"
#include "IMaterial.h"
#include "vec3.h"

class Lambertian : public IMaterial {
public:
	Lambertian(const color& c) : m_albedo(c) {
	}

	virtual bool scatter(const ray& rayIn, const HitRecord& hit, color& attenuation, ray& scattered) const {
		auto scatteredDir = hit.normal + randomUnitVector();
		scattered = ray(hit.p, scatteredDir);
		attenuation = m_albedo;
		return true;
	}

private:
	color m_albedo;
};
