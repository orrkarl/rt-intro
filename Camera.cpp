#include "Camera.h"

Camera::Camera(point3 position, point3 target, vec3 up, double fov, double aspectRatio, double aperture, double focusDist) {
	auto theta = degreesToRadians(fov);
	auto h = tan(theta / 2);
    auto viewportHeight = 2.0 * h;
    auto viewportWidth = aspectRatio * viewportHeight;

	auto forward = normalize(position - target);
	m_u = normalize(cross(up, forward));
	m_v = cross(forward, m_u);

	m_origin = position;
	m_horizontal = focusDist * viewportWidth * m_u;
	m_vertical = focusDist * viewportHeight * m_v; 
	m_lowLeftCorner = m_origin - m_horizontal / 2 - m_vertical / 2 - focusDist * forward; 
	m_lensRadius = aperture / 2;
}

ray Camera::rayAt(double u, double v) const {
	auto rd = m_lensRadius * randomInUnitDisk();
	auto offset = m_u * rd.x + m_v * rd.y;

	return { 
		m_origin + offset, 
		m_lowLeftCorner + u * m_horizontal + v * m_vertical - m_origin - offset
	};
}

