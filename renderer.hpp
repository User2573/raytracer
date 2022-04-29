#pragma once

#include <memory>
#include "math/vector.hpp"
#include "math/ray.hpp"
#include "camera/camera.hpp"
#include "hittable/hittable.hpp"
#include "image/image.hpp"



class Renderer
{
	std::shared_ptr<Image> image;



	Color computeColor(const Ray& ray, const std::shared_ptr<Hittable> scene, const unsigned depth);

public:
	Renderer();

	Renderer(std::shared_ptr<Image> _image);



	void render(const std::shared_ptr<Camera> camera, const std::shared_ptr<Hittable> scene, const unsigned spp, const unsigned depth = 16);
};
