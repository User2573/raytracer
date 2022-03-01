#pragma once

#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "../material/material.hpp"
#include "hitrecord.hpp"
#include "hittable.hpp"



class Sphere : public Hittable
{
public:
	Point position;
	double radius;



	Sphere();

	Sphere(const Point& _point, const double _radius);



	HitRecord hit(const Ray& ray) const override;
};
