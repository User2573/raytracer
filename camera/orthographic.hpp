#pragma once

#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "camera.hpp"



class OrthographicCamera final : public Camera
{
	Vector x, y, z, viewportRight, viewportUp;
	Point position, viewportOrigin;
public:
	OrthographicCamera(Point _lookfrom, Point _lookat, Vector _up, double _aspectRatio);

	virtual Ray getRay(double u, double v) const override;
};
