#pragma once

#include "math/vector.hpp"
#include "math/ray.hpp"
#include "camera/camera.hpp"
#include "hittable/hittable.hpp"
#include "image/image.hpp"



class Renderer
{
	Image* pimage;



	Color computeColor(const Ray& ray, const Hittable* pscene);

public:
	Renderer(Image* _pimage);



	void render(const Camera* pcamera, const Hittable* pscene);
};
