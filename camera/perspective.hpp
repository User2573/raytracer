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
		const double  _fovDeg,
		const double  _aspectRatio,
		const double  _aperture,
		const double  _focalDistance
	);

	Ray getRay(const double u, const double v) const override;
};
