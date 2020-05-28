#pragma once

#include <memory>
#include <vector>

#include "IHittable.h"

class HittableList : public IHittable {
public:
	void clear();

	void add(std::shared_ptr<IHittable> obj);

	bool hit(const ray& r, TBoundaries bounds, HitRecord& rec) const override;

private:
	std::vector<std::shared_ptr<IHittable>> m_hittables;
};
