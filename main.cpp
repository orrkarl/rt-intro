#include "rtintro.h"

#include "Camera.h"
#include "HittableList.h"
#include "Sphere.h"
#include "ray.h"
#include "vec3.h"
#include "ppmutil.h"

vec3 lerp(const vec3& a, const vec3& b, double t) {
	return (1.0 - t) * a + t * b;
}

color rayColor(const ray& ray, const IHittable& world) {
	HitRecord hit;

	if (world.hit(ray, TBoundaries{0, infinity}, hit)) {
		return 0.5 * (hit.normal + color(1, 1, 1));
	}

	auto rayDir = normalize(ray.direction);
	auto colorInterp = 0.5 * (rayDir.y + 1);
	return lerp(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0), colorInterp);
}

int main() {
	constexpr auto aspectRatio = 16.0 / 9.0;
	constexpr uint32_t imageWidth = 384;
	constexpr uint32_t imageHeight = imageWidth / aspectRatio;
	constexpr uint32_t samplesPerPixel = 100;

	HittableList world;
	world.add(std::make_shared<Sphere>(point3(0.0, 0.0, -1.0), 0.5));
	world.add(std::make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100));

	Camera cam;

	std::ofstream resultFile("image.ppm");
	ppm::write::header(imageWidth, imageHeight, resultFile);

	for (auto j = 0u; j < imageHeight; ++j) {
		auto y = imageHeight - 1 - j;
		for (auto x = 0u; x < imageWidth; ++x) {
			color pixelColor;
			for (auto s = 0u; s < samplesPerPixel; ++s) {
				const auto u = (x + nextRandomDouble()) / imageWidth;
				const auto v = (y + nextRandomDouble()) / imageHeight;
				auto r = cam.rayAt(u, v);
				pixelColor += rayColor(r, world) / samplesPerPixel;
			}
			ppm::write::pixel(pixelColor, resultFile);
		}
	}
}

