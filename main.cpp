#include <memory>
#include "math/ray.hpp"
#include "image/image.hpp"
#include "camera/perspective.hpp"
#include "hittable/hitrecord.hpp"
#include "hittable/sphere.hpp"
#include "hittable/hittablelist.hpp"
#include "material/lambertian.hpp"
#include "texture/constant.hpp"
#include "renderer.hpp"


int main()
{
	constexpr int iWidth = 256;
	constexpr int iHeight = 256;
	constexpr double ratio = double(iHeight) / iWidth;
	auto img = std::make_shared<Image>(iWidth, iHeight);

	auto camera = std::make_shared<PerspectiveCamera>(
		rayFromTo({0, 1, 0}, {0, 1, -1}),
		{0, 1, 0},
		75,
		ratio,
		0,
		5
	);

	auto renderer = std::make_shared<Renderer>(img);

	auto red = std::make_shared<ConstantTexture>(rgb(203, 74, 67));
	auto gray = std::make_shared<ConstantTexture>(rgb(127, 127, 127));

	auto diffRed = std::make_shared<LambertianMaterial>(red);
	auto diffGray = std::make_shared<LambertianMaterial>(gray);

	auto s1 = std::make_shared<Sphere>({0, 1, -3}, 1, diffRed);
	double c = 4096; // large constant
	auto floor = std::make_shared<Sphere>({0, -c, 0}, c, &diffGray);

	auto scene = std::make_shared<HittableList>();
	scene->add(s1);
	scene->add(floor);

	renderer->render(camera, scene);
	img->writeToPNG("output.png");
}
