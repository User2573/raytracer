#pragma once
#ifndef ORTHOGRAPHIC_HPP
#define ORTHOGRAPHIC_HPP

#include "icamera.hpp"
#include "../math/vector.hpp"
#include "../math/ray.hpp"



class OrthographicCamera
{
	Vector viewportRight, viewportUp;
	Point position, viewportOrigin;
public:
	OrthographicCamera(Point _lookfrom, Point _lookat, Vector _up, double _aspectRatio);

	virtual ~OrthographicCamera() = default;

	virtual Ray getRay(double u, double v) const override;
};



#endif
