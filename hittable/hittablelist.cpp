#include <memory>
#include "hitrecord.hpp"
#include "hittablelist.hpp"

HittableList::HittableList() {}

// template <typename... Args> HittableList::HittableList(const std::shared_ptr<Hittable> _object, Args... _objects)



void HittableList::clear()
{
	objects.clear();
}

void HittableList::add_impl(const std::initializer_list<std::shared_ptr<Hittable>> newObjects)
{
	for (const std::shared_ptr<Hittable>& newObject : newObjects) {
		objects.push_back(newObject);
	}
}

// template <typename... Args> void HittableList::add(const std::shared_ptr<Hittable> newObject, Args... newObjects)

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
