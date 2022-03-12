#include "../math/vector.hpp"
#include "../hittable/hitrecord.hpp"
#include "constant.hpp"



ConstantTexture::ConstantTexture() : ConstantTexture({0, 0, 0}) {}

ConstantTexture::ConstantTexture(const Color& _color) : color(_color) {}



Color ConstantTexture::value(const HitRecord&) const
{
	return color;
}
