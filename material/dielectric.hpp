#pragma once

#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "../hittable/hitrecord.hpp"
#include "material.hpp"


class DielectricMaterial final : public Material
{
	double reflectance(const double cosine, const double ratio) const;
public:
	double ior;



	DielectricMaterial(const double _ior = 1.5);



	virtual Ray scatter(const Ray& ray, const HitRecord& record) const override;
};
