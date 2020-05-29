#include "ppmutil.h"

double applyGamma(double c) {
	return std::sqrt(c);
}

template <typename T>
T clamp(T value, T min, T max) {
	return std::max(min, std::min(value, max));
}

double processColor(double c) {
	return clamp(applyGamma(c), 0.0, 0.999);
}

namespace ppm {

namespace write {

void header(uint32_t w, uint32_t h, std::ostream& out) {
	out << "P3\n" << w << ' ' << h << "\n255\n";
}

void pixel(uint8_t r, uint8_t g, uint8_t b, std::ostream& out) {
	out << int(r) << ' ' << int(g) << ' ' << int(b) << '\n';	
}

void pixel(double r, double g, double b, std::ostream& out) {
	auto ir = static_cast<uint8_t>(255.999 * processColor(r));
	auto ig = static_cast<uint8_t>(255.999 * processColor(g));
	auto ib = static_cast<uint8_t>(255.999 * processColor(b));
	pixel(ir, ig, ib, out);
}

void pixel(const vec3& v, std::ostream& out) {
	pixel(v.x, v.y, v.z, out);
}

}

}

