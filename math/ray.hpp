#pragma once

#include <iostream>
#include "vector.hpp"



class Ray
{
public:
	Point origin;
	Vector direction;
	Color attenuation;
	bool scattered;



	Ray();

	Ray(const Vector& _direction);

	Ray(const Point& _origin, const Vector& _direction);

	Ray(const Point& _origin, const Vector& _direction, const Color& _attenuation);

	Ray(const Point& _origin, const Vector& _direction, const Color& _attenuation, const bool _scattered);



	Point at(const double t) const;

	Ray& normalizeDirection();

	Ray& lookAt(const Point& p);

	friend std::ostream& operator << (std::ostream &os, const Ray& ray);
};



Ray rayFromTo(const Point& from, const Point& to);

Ray rayFromTo(const Point& from, const Point& to, const Color& attenuation);

Ray rayFromTo(const Point& from, const Point& to, const Color& attenuation, const bool scattered);
