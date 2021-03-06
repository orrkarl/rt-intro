#pragma once

#include "rtintro.h"

class vec3 {
public:
	inline static vec3 random() {
		return {nextRandomDouble(), nextRandomDouble(), nextRandomDouble()};
	}

	inline static vec3 random(double min, double max) {
		return {nextRandomDouble(min, max), nextRandomDouble(min, max), nextRandomDouble(min, max)};
	}

	vec3() : vec3(0.0, 0.0, 0.0) {
	}

	vec3(double x, double y, double z)
		: data{x, y, z} {
	}

	vec3 operator-() const {
		return {-x, -y, -z};
	}

	vec3& operator-=(const vec3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	vec3& operator+=(const vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3& operator*=(const vec3& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	vec3& operator/=(const vec3& v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	double lengthSquared() const {
		return x * x + y * y + z * z;
	}

	double length() const {
		return std::sqrt(lengthSquared()); 
	}

public:
	union {
		double data[3];
		struct { 
			double x;
			double y;
			double z;
		};
	};
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline vec3 operator+(const vec3& lhs, const vec3& rhs) {
	return {
		lhs.x + rhs.x,
		lhs.y + rhs.y,
		lhs.z + rhs.z
	};
}

inline vec3 operator-(const vec3& lhs, const vec3& rhs) {
	return lhs + (-rhs);
}

inline vec3 operator*(const vec3& lhs, const vec3& rhs) {
	return {
		lhs.x * rhs.x,
		lhs.y * rhs.y,
		lhs.z * rhs.z
	};
}

inline vec3 operator/(const vec3& lhs, const vec3& rhs) {
	return {
		lhs.x / rhs.x,
		lhs.y / rhs.y,
		lhs.z / rhs.z
	};
}

inline vec3 operator*(const vec3& v, double t) {
	return {
		t * v.x,
		t * v.y,
		t * v.z
	};
}

inline vec3 operator*(double t, const vec3& v) {
	return v * t;
}

inline vec3 operator/(const vec3& v, double t) {
	return v * (1 / t);
}

inline double dot(const vec3& lhs, const vec3& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return {
		u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x
	};
}

inline vec3 normalize(const vec3& v) {
	return v / v.length();
}

inline vec3 randomInUnitSphere() {
	while (true) {
		auto vec = vec3::random(-1, 1);
		if (vec.lengthSquared() >= 1) {
			return vec;
		}
	}
}

inline vec3 randomUnitVector() {
	auto a = nextRandomDouble(0, 2 * M_PI);
	auto z = nextRandomDouble(-1.0, 1.0);
	auto r = std::sqrt(1 - z * z);
	return {r * std::cos(a), r * std::sin(a), z};
}

inline vec3 randomInUnitDisk() {
	while (true) {
		vec3 p(nextRandomDouble(-1, 1), nextRandomDouble(-1, 1), 0);
		if (p.lengthSquared() < 1) {
			return p;
		}
	}
}

inline vec3 reflect(const vec3& v, const vec3& normal) {
	return v - 2 * dot(v, normal) * normal;
}

