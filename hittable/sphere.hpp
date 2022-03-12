#pragma once

#include <memory>
#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "../material/material.hpp"
#include "hitrecord.hpp"
#include "hittable.hpp"



class Sphere final : public Hittable
{
public:
	Point position;
	double radius;

private:
	std::shared_ptr<Material> material;

public:
	Sphere();

	Sphere(const Point& _point, const double _radius, const std::shared_ptr<Material> _material);



	HitRecord hit(const Ray& ray) const override;
};
