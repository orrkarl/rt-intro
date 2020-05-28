#pragma once

#include <cstdint>
#include <ostream>

#include "vec3.h"

namespace ppm {

namespace write {

void header(uint32_t w, uint32_t h, std::ostream& out); 

void pixel(uint8_t r, uint8_t g, uint8_t b, std::ostream& out); 

void pixel(double r, double g, double b, std::ostream& out); 

void pixel(const vec3& v, std::ostream& out); 

}

}

