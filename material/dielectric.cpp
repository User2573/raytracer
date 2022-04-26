#include <cmath>
#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "../math/random.hpp"
#include "../hittable/hitrecord.hpp"
#include "dielectric.hpp"



DielectricMaterial::DielectricMaterial(const double _ior) : ior(_ior) {}



Ray DielectricMaterial::scatter(const Ray& ray, const HitRecord& record) const
{
	double ratio = record.inside ? ior : (1.0 / ior);
	double cosTheta = std::min(dot(-ray.direction, record.normal), 1.0);
	double sinTheta = std::sqrt(1.0 - cosTheta*cosTheta);

	bool cannotRefract = 1.0 < ratio * sinTheta;
	Vector direction{};
	if (false && cannotRefract){// || reflectance(cosTheta, ratio) > random01()) { // more likely to reflect near edge
		direction = ray.direction - 2*dot(ray.direction, record.normal)*record.normal;
	} else {
		const Vector perp = ratio * (ray.direction + cosTheta*record.normal);
		const Vector par = -std::sqrt(std::abs(1.0 - length2(perp))) * record.normal;
		direction = perp + par;
	}

	return Ray{
		record.point,
		direction,
		Color{1}
	};
}

double DielectricMaterial::reflectance(const double cosine, const double ratio) const
{
	// schlick's approximation
	auto r0 = (1.0 - ratio) / (1.0 + ratio);
	r0 = r0*r0;
	return r0 + (1.0 - r0) * std::pow(1 - cosine, 5);
}
