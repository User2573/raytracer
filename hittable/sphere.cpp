#include <cmath>
#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "hitrecord.hpp"
#include "sphere.hpp"



Sphere::Sphere() : Sphere({0, 0, 0} , 1) {}

Sphere::Sphere(const Point& _position, const double _radius)
: position(_position), radius(_radius) {}



HitRecord Sphere::hit(const Ray& ray) const
{
/*	// thank you scratchapixel!
	Vector l = position - ray.origin;
	double tca = dot(l, ray.direction);
	if (tca < 0.0) return HitRecord{false};
	double d2 = length2(l) - tca*tca;
	double r2 = radius*radius;
	if (d2 > r2) return HitRecord{false};
	double t = tca + std::sqrt(r2 - d2); // second intersection at ray.at(tca - sqrt) but it's always farther
	if (t < 0) return HitRecord{false};
	Point p = ray.at(t);
*/	Vector oc = ray.origin - position;
	double a = length2(ray.direction);
	double b = dot(oc, ray.direction);
	double c = length2(oc) - radius*radius;
	double discrim = b*b - a*c;

	if (discrim < 0.0)
		return HitRecord{false};

	double t = (-b - std::sqrt(discrim)) / a;
	Vector p = ray.at(t);
	return HitRecord{
		t,
		p,
		normalize(p - position),
		nullptr
	};
}
