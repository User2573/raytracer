#include <algorithm>
#include <cmath>
#include <memory>
#include <numbers>
#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "hitrecord.hpp"
#include "sphere.hpp"



Sphere::Sphere(const Point& _position, const double _radius, const std::shared_ptr<Material> _material)
: position(_position), radius(_radius), material(_material) {}



HitRecord Sphere::hit(const Ray& ray) const
{
	// thank you scratchapixel!
	Vector l = position - ray.origin;
	double tca = dot(l, ray.direction);
//	if (tca < 0.0) return HitRecord{false};
	double d2 = length2(l) - tca*tca;
	double r2 = radius*radius;
	if (d2 > r2) return HitRecord{false};
	double thc = std::sqrt(r2 - d2);
	double t0 = tca - thc, t1 = tca + thc;

/*	Vector oc = ray.origin - position;
	double a = length2(ray.direction);
	double hb = dot(oc, ray.direction);
	double c = length2(oc) - radius*radius;

	double discrim = hb*hb - a*c;
	if (discrim < 0.0) return HitRecord{false};

	double sqrtd = std::sqrt(discrim);
	double t = (-hb - sqrtd) / a;
	if (t < 0.0) {
		t = (-hb + sqrtd) / a;
		if (t < 0.0) return HitRecord{false};
	}
*/
	if (t1 < t0) std::swap(t0, t1);
	if (t0 < 0) {
		t0 = t1;
		if (t0 < 0) return HitRecord{false};
	}

	Point p = ray.at(t0);
	Vector n = normalize(p - position); // outward normal
	bool inside = 0.0 < dot(ray.direction, n);
	return HitRecord{
		inside,
		t0,
		p,
		inside ? -n : n, // flip normal if inside
		0.5 + atan2(-p.z, p.x) / (2*std::numbers::pi),
		acos(-p.y) / std::numbers::pi,
		material
	};
}
