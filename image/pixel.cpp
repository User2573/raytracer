#include <cmath>
#include <iostream>
#include "../math/vector.hpp"
#include "pixel.hpp"



Pixel::Pixel() = default;

Pixel::Pixel(const Color& _value) : value(_value), x(0), y(0) {}

Pixel::Pixel(const Color& _value, const int _x, const int _y) : value(_value), x(_x), y(_y) {}



std::ostream& operator << (std::ostream& os, const Pixel& pixel)
{
	constexpr double gamma = 1.0 / 2.2;
	os << static_cast<unsigned char>(
		255.0 * std::pow(std::clamp(pixel.value.x, 0.0, 1.0), gamma)
	)
	   << static_cast<unsigned char>(
		255.0 * std::pow(std::clamp(pixel.value.y, 0.0, 1.0), gamma)
	)
	   << static_cast<unsigned char>(
		255.0 * std::pow(std::clamp(pixel.value.z, 0.0, 1.0), gamma)
	);
	return os;
}
