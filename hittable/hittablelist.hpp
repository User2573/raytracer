#pragma once

#include <memory>
#include <initializer_list>
#include <vector>
#include "hitrecord.hpp"
#include "hittable.hpp"



class HittableList : public Hittable
{
	std::vector<std::shared_ptr<Hittable>> objects;



	// bruh
	void add_impl(const std::initializer_list<std::shared_ptr<Hittable>> newObjects);

public:
	HittableList();

	template <typename... Args>
	HittableList(const std::shared_ptr<Hittable> _object, Args... _objects);



	void clear();

	template <typename... Args>
	void add(const std::shared_ptr<Hittable> newObject, Args... newObjects);



	HitRecord hit(const Ray& ray) const override;
};



// damn templates...
template <typename... Args>
HittableList::HittableList(const std::shared_ptr<Hittable> _object, Args... _objects)
{
	add_impl({_object, _objects...});
}

template <typename... Args>
void HittableList::add(const std::shared_ptr<Hittable> newObject, Args... newObjects)
{
	add_impl({newObject, newObjects...});
}
