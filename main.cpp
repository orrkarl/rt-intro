#include "rtintro.h"

#include "Camera.h"
#include "Dielectric.h"
#include "HittableList.h"
#include "IMaterial.h"
#include "Lambertian.h"
#include "Metal.h"
#include "ray.h"
#include "Sphere.h"
#include "vec3.h"
#include "ppmutil.h"

vec3 lerp(const vec3& a, const vec3& b, double t) {
	return (1.0 - t) * a + t * b;
}

color rayColor(const ray& r, const IHittable& world, uint64_t depth) {
	if (depth == 0) {
		return color(0.0, 0.0, 0.0);
	}

	HitRecord hit;

	if (world.hit(r, TBoundaries{0.0001, infinity}, hit)) {
		ray scattered;
		color attenuation;
		if (hit.materialPtr->scatter(r, hit, attenuation, scattered)) {
			return attenuation * rayColor(scattered, world, depth - 1);
		}

		return color(0.0, 0.0, 0.0);
	}

	auto rayDir = normalize(r.direction);
	auto colorInterp = 0.5 * (rayDir.y + 1);
	return lerp(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0), colorInterp);
}

int main() {
	constexpr auto aspectRatio = 16.0 / 9.0;
	constexpr uint32_t imageWidth = 384;
	constexpr uint32_t imageHeight = imageWidth / aspectRatio;
	constexpr uint32_t samplesPerPixel = 100;
	constexpr uint64_t maxDepth = 50;

	auto R = std::cos(pi / 4);
	HittableList world;
	world.add(make_shared<Sphere>(point3(-R,0,-1), R, make_shared<Lambertian>(color(0, 0, 1))));
	world.add(make_shared<Sphere>(point3( R,0,-1), R, make_shared<Lambertian>(color(1, 0, 0)))); 

	Camera cam(90, double(imageWidth) / imageHeight);

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
				pixelColor += rayColor(r, world, maxDepth) / samplesPerPixel;
			}
			ppm::write::pixel(pixelColor, resultFile);
		}
	}
}

