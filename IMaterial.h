#pragma once

#include "IHittable.h"
#include "ray.h"
#include "rtintro.h"
#include "vec3.h"

class IMaterial {
public:
	virtual bool scatter(const ray& rayIn, const HitRecord& record, color& attenuation, ray& scattered) const = 0;
};
