#include "../math/vector.hpp"
class Material;
#include "hitrecord.hpp"



HitRecord::HitRecord() : HitRecord(false) {}

HitRecord::HitRecord(const bool _hit)
: hit(_hit), inside(), t(), point(), normal(), u(0), v(0), material() {}

HitRecord::HitRecord(const bool _inside, const double _t, const Point& _point, const Vector& _normal, const std::shared_ptr<Material> _material)
: HitRecord(_inside, _t, _point, _normal, 0, 0, _material) {}

HitRecord::HitRecord(const bool _inside, const double _t, const Point& _point, const Vector& _normal, const double _u, const double _v, const std::shared_ptr<Material> _material)
: hit(0 < _t), inside(_inside), t(_t), point(_point), normal(_normal), u(_u), v(_v), material(_material) {}

