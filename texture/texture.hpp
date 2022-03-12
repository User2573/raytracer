#pragma once

#include "../math/vector.hpp"



class Texture
{
public:
	virtual Color value(const HitRecord& record) const = 0;
};
