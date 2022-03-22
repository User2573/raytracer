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
	Point p = ray.at(t);

	Vector up = Vector{1, 0, 0};
	if (length2(up - normal) < 1e-8) up = Vector{0, 0, 1};
	Vector u = normalize(cross(normal, up));
	Vector v = cross(normal, u);

	return HitRecord{
		otherside,
		t,
		p,
		otherside ? -normal : normal,
		dot(p, u), dot(p, v),
		material
	};
}
