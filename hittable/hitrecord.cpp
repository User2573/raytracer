#include "../math/vector.hpp"
class Material;
#include "hitrecord.hpp"



HitRecord::HitRecord() : HitRecord(false) {}

HitRecord::HitRecord(const bool _hit)
: hit(_hit), t(), point(), normal(), pmaterial(nullptr) {}

HitRecord::HitRecord(const double _t, const Point& _point, const Vector& _normal, Material* const _pmaterial)
: hit(0 < _t), t(_t), point(_point), normal(_normal), pmaterial(_pmaterial) {}

