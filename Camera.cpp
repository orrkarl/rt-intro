#include "Camera.h"

Camera::Camera(point3 position, point3 target, vec3 up, double fov, double aspectRatio) {
	auto theta = degreesToRadians(fov);
	auto h = tan(theta / 2);
    auto viewportHeight = 2.0 * h;
    auto viewportWidth = aspectRatio * viewportHeight;

	auto offset = normalize(position - target);
	auto u = normalize(cross(up, offset));
	auto v = cross(offset, u);

	m_origin = position;

	m_horizontal = viewportWidth * u;
	m_vertical = viewportHeight * v;
	m_lowLeftCorner = m_origin - m_horizontal / 2 - m_vertical / 2 - offset;
}

ray Camera::rayAt(double u, double v) const {
	return { m_origin, m_lowLeftCorner + u * m_horizontal + v * m_vertical - m_origin };
}

