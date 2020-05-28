#include "HittableList.h"

void HittableList::clear() {
	m_hittables.clear();
}

void HittableList::add(std::shared_ptr<IHittable> obj) {
	m_hittables.push_back(obj);
}

bool HittableList::hit(const ray& r, TBoundaries bounds, HitRecord& rec) const {
	HitRecord temp;
	bool anyHit = false;

	for (const auto& obj : m_hittables) {
		if (obj->hit(r, bounds, temp)) {
			anyHit = true;
			bounds.max = temp.t;
		}
	}

	rec = temp;
	return anyHit;
}

