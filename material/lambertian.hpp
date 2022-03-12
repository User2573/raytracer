#pragma once

#include <memory>
#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "../texture/texture.hpp"
#include "material.hpp"



class LambertianMaterial final : public Material
{
	std::shared_ptr<Texture> albedo;

public:
	LambertianMaterial();

	LambertianMaterial(const Color& _color);

	LambertianMaterial(const std::shared_ptr<Texture> _albedo);



	Ray scatter(const Ray& ray, const HitRecord& record) const override;
};
