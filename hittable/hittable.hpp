#pragma once

#include "../math/ray.hpp"
#include "hitrecord.hpp"



class Hittable
{
public:
	virtual ~Hittable() {};



	virtual HitRecord hit(const Ray& ray) const = 0;
};
