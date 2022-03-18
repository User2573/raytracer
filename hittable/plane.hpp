#pragma once

#include <memory>
#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "../material/material.hpp"
#include "hitrecord.hpp"
#include "hittable.hpp"



class Plane : public Hittable
{
public:
	Vector normal;
	double distance;

private:
	std::shared_ptr<Material> material;

public:
	Plane();

	Plane(const Vector& _normal, const double _distance);

	Plane(const Vector& _normal, const double _distance, const std::shared_ptr<Material> _material);



	HitRecord hit(const Ray& ray) const override;
};
