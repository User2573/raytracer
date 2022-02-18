#pragma once
#ifndef PERSPECTIVE_HPP
#define PERSPECTIVE_HPP

#include "../math/ray.hpp"
#include "../math/vector.hpp"
#include "icamera.hpp"



class PerspectiveCamera : public ICamera
{
	Vector x, y, z, viewportRight, viewportUp;
	Point position, viewportOrigin;
	double lensRadius;

public:
	PerspectiveCamera(Point _lookfrom, Point _lookat, Vector _up, double _fov, double _aspectRatio, double _aperture, double _focalDistance);

	virtual ~PerspectiveCamera() = default;

	virtual Ray getRay(double u, double v) const override;
};



#endif
