#pragma once

#include <memory>
#include "../math/vector.hpp"
class Material; // material.hpp includes this file :C



class HitRecord
{
public:
	bool hit, inside;
	double t;
	Point point;
	Vector normal;
	double u, v;
	std::shared_ptr<Material> material;



	HitRecord();

	HitRecord(const bool _hit);

	HitRecord(const bool _inside, const double _t, const Point& _point, const Vector& _normal, const std::shared_ptr<Material> _material);

	HitRecord(const bool _inside, const double _t, const Point& _point, const Vector& _normal, const double _u, const double _v, const std::shared_ptr<Material> _material);
};
