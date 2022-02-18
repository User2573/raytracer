#pragma once
#ifndef ICAMERA_HPP
#define ICAMERA_HPP

#include "../math/ray.hpp"



class ICamera
{
public:
	virtual ~ICamera() = default;

	virtual Ray getRay(double u, double v) const
	{
		return {};
	}
};



#endif
