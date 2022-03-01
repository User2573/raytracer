#include <cmath>
//#include <memory>
#include "math/vector.hpp"
#include "math/ray.hpp"
#include "math/random.hpp"
#include "image/image.hpp"
#include "hittable/hitrecord.hpp"
#include "hittable/hittable.hpp"
#include "renderer.hpp"



Renderer::Renderer(Image* _pimage) : pimage(_pimage) {}

Color Renderer::computeColor(const Ray& ray, const Hittable* pscene)
{
	Color color;
	HitRecord record = pscene->hit(ray);

	if (record.hit) {
		color = (record.normal + 1) / 2;
	}

	else {
		color = 0.18;
	}

	return color;
}

/*==================================================================
              WARNING : terrible handwritten code ahead
==================================================================*/
void Renderer::render(const Camera* pcamera, const Hittable* pscene)
{
	int n = 4;
	double dist = 1.0 / (n + 2);
	double invn2 = 1.0 / (n*n); // division bad hurrr
	double invw = 1.0 / pimage->width;
	double invh = 1.0 / pimage->height;
	pimage->for_each(
		[&](Color& color, int x, int y) {
			// equidistant grid supersampling, best i can do
			Vector sum{};
			for (int u = 0; u < n; ++u) {
				for (int v = 0; v < n; ++v) {
					Ray ray = pcamera->getRay( // convoluted shit, don't touch
						(x + dist*(1 + 2*u)) * invw,
						(y + dist*(1 + 2*v)) * invh
					);
					// calculate da color
					sum += computeColor(ray, pscene);
				}
			}
			color = sum * invn2;	
		}
	);
}
