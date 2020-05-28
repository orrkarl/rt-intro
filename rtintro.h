#pragma once

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degreesToRadians(double degrees) {
    return degrees * pi / 180;
}

inline double nextRandomDouble() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double nextRandomDouble(double min, double max) {
	return min + nextRandomDouble() * (max - min);
}

// Common Headers

#include "ray.h"
#include "vec3.h"
#include "ppmutil.h"

