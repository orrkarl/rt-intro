#pragma once

#include "rtintro.h"
#include "IHittable.h"
#include "IMaterial.h"
#include "ray.h"
#include "vec3.h"

namespace dielectric_factor {

constexpr double AIR = 1.0;
constexpr double DIAMOND = 2.4;
constexpr double GLASS = 1.5;

}

class Dielectric : public IMaterial {
public:
	Dielectric(double refractionCoeff) : m_refractionCoeff(refractionCoeff) {
	}

	virtual bool scatter(
            const ray& rayIn, const HitRecord& hit, color& attenuation, ray& scattered) const {
		double snellRatio = hit.frontFace ? (1.0 / m_refractionCoeff) : m_refractionCoeff;
		auto refractionDir = snellRefract(normalize(rayIn.direction), hit.normal, snellRatio);

		attenuation = color(1.0, 1.0, 1.0);
		scattered = ray(hit.p, refractionDir);

		return true;
	}

private:
	double m_refractionCoeff;
};

