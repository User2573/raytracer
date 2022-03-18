#include <memory>
#include "math/ray.hpp"
#include "image/image.hpp"
#include "camera/perspective.hpp"
#include "hittable/hitrecord.hpp"
#include "hittable/sphere.hpp"
#include "hittable/plane.hpp"
#include "hittable/hittablelist.hpp"
#include "material/lambertian.hpp"
#include "texture/constant.hpp"
#include "renderer.hpp"


int main(int argc, char* argv[]) // parsing... later
{
	auto gray = std::make_shared<ConstantTexture>(rgb(127, 127, 127));
	auto red = std::make_shared<ConstantTexture>(rgb(203, 74, 67));
	auto orange = std::make_shared<ConstantTexture>(rgb(221, 147, 73));
	auto yellow = std::make_shared<ConstantTexture>(rgb(216, 192, 71));

	auto diffGray = std::make_shared<LambertianMaterial>(gray);
	auto diffRed = std::make_shared<LambertianMaterial>(red);
	auto diffOrange = std::make_shared<LambertianMaterial>(orange);
	auto diffYellow = std::make_shared<LambertianMaterial>(yellow);



	constexpr int iWidth = 448; // 1.75 * 256
	constexpr int iHeight = 256;
	auto img = std::make_shared<Image>(iWidth, iHeight);



	constexpr double r = .2;
	auto s1 = std::make_shared<Sphere>(Point{0, r, -5}, r, diffRed);
	auto s2 = std::make_shared<Sphere>(Point{0, r, -4}, r, diffOrange);
	auto s3 = std::make_shared<Sphere>(Point{0, r, -3}, r, diffYellow);
	auto floor = std::make_shared<Plane>(Vector{0, 1, 0}, 0, diffGray);



	auto camera = std::make_shared<PerspectiveCamera>(
		rayFromTo({0, 1.7, 0}, {0, 1.5, -1}),
		Vector{0, 1, 0},
		70_deg,
		iWidth, iHeight,
		0,
		5
	);



	auto renderer = std::make_shared<Renderer>(img);

	auto scene = std::make_shared<HittableList>();
	scene->add(s1);
	scene->add(s2);
	scene->add(s3);
	scene->add(floor);

	renderer->render(camera, scene);
	img->writeToPNG("output.png");
}
