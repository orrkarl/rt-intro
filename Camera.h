#pragma once

#include "rtintro.h"
#include "ray.h"
#include "vec3.h"

class Camera {
public:
	Camera(point3 position, point3 target, vec3 up, double fov, double aspectRatio, double aperture, double focusDist);

	ray rayAt(double u, double v) const;

private:
	point3 m_origin;
	point3 m_lowLeftCorner;
	vec3 m_horizontal;
	vec3 m_vertical;
	vec3 m_u;
	vec3 m_v;
	double m_lensRadius;
};

