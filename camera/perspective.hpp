#pragma once

#include <numbers>
#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "camera.hpp"



class PerspectiveCamera final : public Camera
{
	Vector x, y, z, viewportRight, viewportUp;
	Point position, viewportOrigin;
	double lensRadius;

public:
	PerspectiveCamera();

	PerspectiveCamera(
		const Ray&    _eye,
		const Vector& _up,
		const double  _vFov,
		const int     _imageWidth,
		const int     _imageHeight,
		const double  _aperture,
		const double  _focalDistance
	);

	Ray getRay(const double u, const double v) const override;
};



constexpr double operator "" _deg(unsigned long long int x)
{
	return static_cast<double>(x) * std::numbers::pi / 180.0;
}

constexpr double operator "" _deg(long double x)
{
	return x * std::numbers::pi / 180.0;
}
