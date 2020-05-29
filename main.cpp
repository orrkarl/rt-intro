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

HittableList randomizeScene() {
    HittableList world;

    auto ground_material = make_shared<Lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = nextRandomDouble();
            point3 center(a + 0.9*nextRandomDouble(), 0.2, b + 0.9*nextRandomDouble());

            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<IMaterial> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = nextRandomDouble(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

int main() {
	constexpr auto aspectRatio = 16.0 / 9.0;
	constexpr uint32_t imageWidth = 1280;
	constexpr uint32_t imageHeight = imageWidth / aspectRatio;
	constexpr uint32_t samplesPerPixel = 100;
	constexpr uint64_t maxDepth = 50;
	constexpr auto aperture = 0.1;

	auto world = randomizeScene();

    point3 lookfrom(13,2,3);
    point3 lookat(0,0,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;

    Camera cam(lookfrom, lookat, vup, 20, aspectRatio, aperture, dist_to_focus);

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

