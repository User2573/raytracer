#include <iostream>
#include "ray.hpp"
#include "vector.hpp"



Ray::Ray() : origin(), direction() {}

Ray::Ray(const Vector& _direction) : origin(), direction(_direction)
{
	normalizeDirection();
}

Ray::Ray(const Point& _origin, const Vector& _direction) : origin(_origin), direction(_direction)
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
	"    origin:    " << ray.origin << ",\n"
	"    direction: " << ray.direction << "\n"
	"}";
	return os;
}

Ray rayFromTo(const Point& from, const Point& to)
{
	return Ray(from, to - from);
}
