#include <iostream>
#include "ray.hpp"
#include "vector.hpp"



Ray::Ray() : Ray({0, 0, 0}, {0, 0, 1}) {}

Ray::Ray(const Vector& _direction) : Ray({0, 0, 0}, _direction) {}

Ray::Ray(const Point& _origin, const Vector& _direction) : Ray(_origin, _direction, {0, 0, 0}, false) {}

Ray::Ray(const Point& _origin, const Vector& _direction, const Color& _attenuation) : Ray(_origin, _direction, _attenuation, true) {}

Ray::Ray(const Point& _origin, const Vector& _direction, const Color& _attenuation, const bool _scattered)
: origin(_origin), direction(_direction), attenuation(_attenuation), scattered(_scattered)
{
	normalizeDirection();
}



Point Ray::at(const double t) const
{
	return origin + t*direction;
}

Ray& Ray::normalizeDirection()
{
	if (length2(direction) != 1.0) {
		direction.normalize();
	}
	return *this;
}

Ray& Ray::lookAt(const Point& p)
{
	direction = p - origin;
	return normalizeDirection();
}

std::ostream& operator << (std::ostream& os, const Ray& ray)
{
	os << "Ray{\n"
	"    origin     : " << ray.origin << ",\n"
	"    direction  : " << ray.direction << ",\n"
	"    attenuation: " << ray.attenuation << ",\n"
	"    scattered  : " << ray.scattered << "\n"
	"}";
	return os;
}

Ray rayFromTo(const Point& from, const Point& to)
{
	return Ray{from, to - from};
}

Ray rayFromTo(const Point& from, const Point& to, const Color& attenuation)
{
	return Ray{from, to - from, attenuation};
}

Ray rayFromTo(const Point& from, const Point& to, const Color& attenuation, const bool scattered)
{
	return Ray{from, to - from, attenuation, scattered};
}
