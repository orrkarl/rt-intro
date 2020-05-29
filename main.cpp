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

	HittableList world;
	world.add(make_shared<Sphere>(point3(0.0, 0.0, -1.0), 0.5, make_shared<Lambertian>(color(0.1, 0.2, 0.5))));
	world.add(make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100, make_shared<Lambertian>(color(0.8, 0.8, 0.0))));
	world.add(make_shared<Sphere>(point3(1,0,-1), 0.5, make_shared<Metal>(color(.8,.6,.2), 0.0)));
    world.add(make_shared<Sphere>(point3(-1,0,-1), 0.5, make_shared<Dielectric>(dielectric_factor::GLASS)));
    world.add(make_shared<Sphere>(point3(-1,0,-1), -0.45, make_shared<Dielectric>(dielectric_factor::GLASS)));

	Camera cam(point3(-2,2,1), point3(0,0,-1), vec3(0,1,0), 20, aspectRatio);

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

