#include "Camera.h"

Camera::Camera(double fov, double aspectRatio) {
	auto theta = degreesToRadians(fov);
	auto h = tan(theta / 2);
    auto viewportHeight = 2.0 * h;
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focalLength = 1.0;

	m_origin = point3(0.0, 0.0, 0.0);
	m_horizontal = vec3(viewportWidth, 0.0, 0.0);
	m_vertical = vec3(0.0, viewportHeight, 0.0);
	m_lowLeftCorner = m_origin - m_horizontal / 2 - m_vertical / 2 - vec3(0, 0, focalLength);
}

ray Camera::rayAt(double u, double v) const {
	return { m_origin, m_lowLeftCorner + u * m_horizontal + v * m_vertical - m_origin };
}

