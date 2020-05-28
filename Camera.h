#pragma once

#include "rtintro.h"

class Camera {
public:
	Camera();

	ray rayAt(double u, double v) const;

private:
	point3 m_origin;
	point3 m_lowLeftCorner;
	vec3 m_horizontal;
	vec3 m_vertical;
};

