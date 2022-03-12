#pragma once

#include "../math/vector.hpp"
#include "../hittable/hitrecord.hpp"
#include "texture.hpp"



class ConstantTexture : public Texture
{
public:
	Color color;

public:
	ConstantTexture();

	ConstantTexture(const Color& _color);



	Color value(const HitRecord& record) const override;
};
