#pragma once

#include <memory>
#include <vector>
#include "hitrecord.hpp"
#include "hittable.hpp"



class HittableList : public Hittable
{
	std::vector<std::shared_ptr<Hittable>> objects;

public:
	HittableList();

	HittableList(const std::shared_ptr<Hittable> _object);



	void clear();

	void add(const std::shared_ptr<Hittable> object);



	HitRecord hit(const Ray& ray) const override;
};
