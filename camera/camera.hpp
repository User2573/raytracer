#pragma once

#include "../math/ray.hpp"



class Camera
{
public:
	virtual ~Camera() {}

	virtual Ray getRay(const double u, const double v) const = 0;
};
