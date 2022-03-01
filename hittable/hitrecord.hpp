#pragma once

#include "../math/vector.hpp"
class Material; // material.hpp includes this file :C

class HitRecord
{
public:
	bool hit;
	double t;
	Point point;
	Vector normal;
	Material* pmaterial;



	HitRecord();
	HitRecord(const bool _hit);
	HitRecord(const double _t, const Point& _point, const Vector& _normal, Material* const _pmaterial);
};
