#pragma once

#include <iostream>
#include "vector.hpp"



class Ray
{
public:
	Point origin;
	Vector direction;



	Ray();

	Ray(const Vector& _direction);

	Ray(const Point& _origin, const Vector& _direction);



	Point at(const double t) const;

	Ray& normalizeDirection();

	Ray& lookAt(const Point& p);

	friend std::ostream& operator << (std::ostream &os, const Ray& ray);
};



Ray rayFromTo(const Point& from, const Point& to);
