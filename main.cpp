#include <cstdint>
#include <iostream>
#include <fstream>

#include "hits.h"
#include "ppmutil.h"
#include "ray3.h"
#include "vec3.h"

vec3 lerp(const vec3& a, const vec3& b, double t) {
	return (1.0 - t) * a + t * b;
}

color rayColor(const ray3& ray) {
	if (doesIntersecteSphere(point3(0.0, 0.0, -1.0), 0.5, ray)) {
		return color(1.0, 0.0, 0.0);
	}

	auto rayDir = normalize(ray.direction);
	auto t = 0.5 * (rayDir.y + 1);
	return lerp(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0), t);
}

int main() {
	constexpr auto aspectRatio = 16.0 / 9.0;
	constexpr uint32_t imageWidth = 384;
	constexpr uint32_t imageHeight = imageWidth / aspectRatio;
	constexpr auto viewportHeight = 2.0;
	constexpr auto viewportWidth = aspectRatio * viewportHeight;
	constexpr auto focalLength = 1.0;

	const vec3 origin(0.0, 0.0, 0.0);
	const vec3 horizontal(viewportWidth, 0.0, 0.0);
	const vec3 vertical(0.0, viewportHeight, 0.0);
	const auto lowLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);

	std::ofstream resultFile("image.ppm");
	ppm::write::header(imageWidth, imageHeight, resultFile);

	for (auto j = 0u; j < imageHeight; ++j) {
		auto y = imageHeight - 1 - j;
		for (auto x = 0u; x < imageWidth; ++x) {
			const auto u = double(x) / imageWidth;
			const auto v = double(y) / imageHeight;
			ray3 r(origin, lowLeftCorner + u * horizontal + v * vertical - origin);
			ppm::write::pixel(rayColor(r), resultFile);
		}
	}
}

