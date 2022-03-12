#pragma once

#include "../math/ray.hpp"
#include "../hittable/hitrecord.hpp"



class Material
{
public:
	virtual Ray scatter(const Ray& ray, const HitRecord& record) const = 0;

	virtual Color emitted(const HitRecord&) const
	{
		return Color{};
	}
};
