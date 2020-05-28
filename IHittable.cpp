#include "IHittable.h"

bool isInBounds(const TBoundaries& bounds, double t) {
	return bounds.min < t && t < bounds.max;
}
