#pragma once
#ifndef RAY_HPP
#define RAY_HPP

#include <iostream>
#include "vector.hpp"



class Ray
{
public:
	Point origin;
	Vector direction;



	Ray();

	Ray(const Vector _direction);

	Ray(const Point _origin, const Vector _direction);



	Point pointAt(double t) const;

	Ray& normalizeDirection();

	Ray& lookAt(const Point& p);



	friend std::ostream& operator << (std::ostream &os, const Ray& ray);
};



Ray rayFromTo(Point from, Point to);



#endif
