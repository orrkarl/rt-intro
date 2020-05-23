#include <cstdint>
#include <iostream>
#include <fstream>

#include "vec3.h"
#include "ppmutil.h"

int main() {
	constexpr uint32_t imageWidth = 256;
	constexpr uint32_t imageHeight = 256;

	std::ofstream resultFile("image.ppm");

	ppm::write::header(imageWidth, imageHeight, resultFile);
	for (auto j = 0u; j < imageHeight; ++j) {
		auto y = imageHeight - 1 - j;
		for (auto x = 0u; x < imageWidth; ++x) {
			auto r = double(x) / imageWidth;
			auto g = double(y) / imageHeight;
			auto b = 0.25;

			ppm::write::pixel(r, g, b, resultFile);
		}
	}
}

