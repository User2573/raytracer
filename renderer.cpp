#include <cmath>
#include <execution>
#include <memory>
#include <iostream>
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

int current = -1;
Color Renderer::computeColor(const Ray& ray, const std::shared_ptr<Hittable> scene, const unsigned depth)
{
	Color color{};
	HitRecord record = scene->hit(ray);

	if (current < depth) std::cout << depth << '\n', current = depth;
	
	if (record.hit) {
		Ray scattered = record.material->scatter(ray, record);
		Color emitted = record.material->emitted(record);
		const Vector biasNormal = dot(scattered.direction, record.normal) < 0 ? -record.normal : record.normal;
		const Vector bias = 2e-8 * biasNormal;
		scattered.origin += bias;

		if (0 < depth) {
			constexpr int samples = 16;
			Color incoming{};
			for (int i = 0; i < samples; ++i)
				incoming += computeColor(scattered, scene, depth - 1);
			incoming /= samples;
			color = emitted + scattered.attenuation * incoming;
		} else {
			color = emitted;
		}
	}

	else { // TODO: add skybox class? together with scene?
		double t = std::clamp(ray.direction.y, 0.0, 1.0);
		color = lerp(rgb(255, 255, 255), rgb(84, 115, 197), t);
	}

	return color;
}

/*================================================================
              WARNING : terrible handwritten code ahead
================================================================*/
void Renderer::render(const std::shared_ptr<Camera> camera, const std::shared_ptr<Hittable> scene, const unsigned spp, const unsigned depth)
{
	const unsigned n = static_cast<unsigned>(std::sqrt(spp));
	const unsigned r = spp - n*n;
	const double dist = 1.0 / (n + 2);
//	const double invn2 = 1.0 / (n*n); // division bad hurrr
//	const double invw = 1.0 / image->width;
//	const double invh = 1.0 / image->height;
	//image->for_each([&](Color color, int x, int y) {
	std::for_each(std::execution::par_unseq, std::begin(*image), std::end(*image),
	[&](Pixel& pixel) {
		// equidistant grid supersampling, best i can do
		const unsigned x = pixel.x;
		const unsigned y = pixel.y;

		Vector sum{};
		for (unsigned u = 0; u < n; ++u) {
			for (unsigned v = 0; v < n; ++v) {
				const Ray ray = camera->getRay(
					(x + dist*(1 + 2*u)) / image->width,
					(y + dist*(1 + 2*v)) / image->height
				);
				sum += computeColor(ray, scene, depth);
			}
		}
		for (unsigned i = 0; i < r; ++i) {
			const Ray ray = camera->getRay(
				(x + randomDouble()) / image->width,
				(y + randomDouble()) / image->height
			);
			sum += computeColor(ray, scene, depth);
		}

		pixel.value = sum / spp;	
	});
}
