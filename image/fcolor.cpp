#include <algorithm>
#include <iostream>
#include "../math/vector.hpp"
#include "fcolor.hpp"

FColor::FColor() : r(0), g(0), b(0) {}

FColor::FColor(const unsigned char _x) : r(_x), g(_x), b(_x) {}

FColor::FColor(const unsigned char _r, const unsigned char _g, const unsigned char _b) : r(_r), g(_g), b(_b) {}

FColor::FColor(const Vector _v)
: r(static_cast<unsigned char>(255.0 * std::clamp(_v.x, 0.0, 1.0)))
, g(static_cast<unsigned char>(255.0 * std::clamp(_v.y, 0.0, 1.0)))
, b(static_cast<unsigned char>(255.0 * std::clamp(_v.z, 0.0, 1.0))) {}



std::ostream& operator << (std::ostream& os, const FColor& color)
{
	os << color.r << color.g << color.b;
	return os;
}
