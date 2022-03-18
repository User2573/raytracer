#include <memory>
#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "../material/material.hpp"
#include "../material/lambertian.hpp"
#include "hitrecord.hpp"
#include "plane.hpp"



Plane::Plane() : Plane(Vector{0, 1, 0}, 0) {}

Plane::Plane(const Vector& _normal, const double _distance)
: Plane(_normal, _distance, std::make_shared<LambertianMaterial>()) {}

Plane::Plane(const Vector& _normal, const double _distance, const std::shared_ptr<Material> _material)
: normal(_normal), distance(_distance), material(_material) {}



HitRecord Plane::hit(const Ray& ray) const
{
	double dn = dot(ray.direction, normal);
	if (-1e-8 < dn && dn < 1e-8) return HitRecord{false};
	double t = (distance * length2(normal) - dot(ray.origin, normal)) / dn;
	bool otherside = 0.0 < dot(ray.direction, normal);
	return HitRecord{
		otherside,
		t,
		ray.at(t),
		otherside ? -normal : normal,
		// uv later
		material
	};
}
