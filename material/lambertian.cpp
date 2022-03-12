#include <memory>
#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "../math/random.hpp"
#include "../hittable/hitrecord.hpp"
#include "lambertian.hpp"



LambertianMaterial::LambertianMaterial()
: albedo(std::make_shared<ConstantTexture>(Color{0.5}) {}

LambertianMaterial::LambertianMaterial(const Color& _color)
: albedo(std::make_shared<ConstantTexture>(_color)) {}

LambertianMaterial::LambertianMaterial(const std::shared_ptr<Texture> _albedo)
: albedo(_albedo) {}



Ray LambertianMaterial::scatter(const Ray&, const HitRecord& record) const
{
	const Vector direction = record.normal + randomUnitVector();
	return Ray{
		record.point,
		length2(direction) < 1e-8 ? record.normal : direction, // catch degenerate scatter direction
		albedo->value(record)
	};
}
