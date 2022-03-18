#pragma once

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



double operator "" _deg(unsigned long long int x);

double operator "" _deg(long double x);
