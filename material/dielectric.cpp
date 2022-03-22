#include <cmath>
#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "../math/random.hpp"
#include "../hittable/hitrecord.hpp"
#include "dielectric.hpp"



DielectricMaterial::DielectricMaterial(const double _ior) : ior(_ior) {}



Ray DielectricMaterial::scatter(const Ray& ray, const HitRecord& record) const
{
	double refractionRatio = record.inside ? ior : (1.0 / ior);
	double cosTheta = std::min(dot(-ray.direction, record.normal), 1.0);
	double sinTheta = std::sqrt(1.0 - cosTheta*cosTheta);

	bool cannotRefract = refractionRatio * sinTheta > 1.0;
	Vector direction;
	if (false){//(cannotRefract || reflectance(cosTheta, refractionRatio) > random01()) { // more likely to reflect near edge
		direction = ray.direction - 2*dot(ray.direction, record.normal)*record.normal;
	} else {
		direction = refractionRatio * (ray.direction + cosTheta*record.normal); // perp. part
		direction -= std::sqrt(std::abs(1.0 - length2(direction))) * record.normal; // add par.
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
