#include <cmath>
#include <memory>
#include "math/vector.hpp"
#include "math/ray.hpp"
#include "math/random.hpp"
#include "image/image.hpp"
#include "hittable/hitrecord.hpp"
#include "hittable/hittable.hpp"
#include "material/material.hpp"
#include "renderer.hpp"



Renderer::Renderer() : image(std::make_shared<Image>()) {}

Renderer::Renderer(const std::shared_ptr<Image> _image) : image(_image) {}

constexpr int maxDepth = 3;
Color Renderer::computeColor(const Ray& ray, const std::shared_ptr<Hittable> scene, const int depth)
{
	Color color;
	HitRecord record = scene->hit(ray);

	if (record.hit) {
		Ray scattered = record.material->scatter(ray, record);
		Vector bias = 1e-4 * record.normal;
		scattered.origin += bias;
		if (depth > maxDepth) {
			color = scattered.attenuation * computeColor(scattered, scene, depth);
		} else {
			color = scattered.attenuation;
		}
	}

	else {
		double t = std::clamp(ray.direction.y, 0.0, 1.0);
		color = lerp(rgb(255, 255, 255), rgb(84, 115, 197), t);
	}

	return color;
}

/*==================================================================
              WARNING : terrible handwritten code ahead
==================================================================*/
void Renderer::render(const std::shared_ptr<Camera> camera, const std::shared_ptr<Hittable> scene)
{
	int n = 8;
	double dist = 1.0 / (n + 2);
	double invn2 = 1.0 / (n*n); // division bad hurrr
	double invw = 1.0 / image->width;
	double invh = 1.0 / image->height;
	pimage->for_each(
		[&](Color& color, int x, int y) {
			// equidistant grid supersampling, best i can do
			Vector sum{};
			for (int u = 0; u < n; ++u) {
				for (int v = 0; v < n; ++v) {
					Ray ray = camera->getRay( // convoluted shit, don't touch
						(x + dist*(1 + 2*u)) * invw,
						(y + dist*(1 + 2*v)) * invh
					);
					// calculate da color
					sum += computeColor(ray, scene);
				}
			}
			color = sum * invn2;	
		}
	);
}
