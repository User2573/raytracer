#include <memory>
#include "hitrecord.hpp"
#include "hittablelist.hpp"

HittableList::HittableList() {}

HittableList::HittableList(const std::shared_ptr<Hittable> _object)
{
	add(_object);
}



void HittableList::clear()
{
	objects.clear();
}

void HittableList::add(const std::shared_ptr<Hittable> object)
{
	objects.push_back(object);
}

HitRecord HittableList::hit(const Ray& ray) const
{
	HitRecord record{false};
	bool isFirstHit = true; // first hit is assigned without comparing t

	for (const std::shared_ptr<Hittable> object : objects) {
		HitRecord tmprecord = object->hit(ray);
		if (tmprecord.hit) {
			if (isFirstHit) {
				record = tmprecord;
				isFirstHit = false;
			} else if (tmprecord.t < record.t) {
				record = tmprecord;
			}
		}
	}

	return record;
}
