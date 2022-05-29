
/*#include <cmath>
#include <memory>
#include "math/ray.hpp"
#include "image/image.hpp"
#include "camera/perspective.hpp"
#include "hittable/hitrecord.hpp"
#include "hittable/sphere.hpp"
#include "hittable/plane.hpp"
#include "hittable/hittablelist.hpp"
#include "material/lambertian.hpp"
#include "material/metal.hpp"
#include "material/dielectric.hpp"
#include "texture/constant.hpp"
#include "texture/checker.hpp"
#include "renderer.hpp"
*/
#include "precompiled.hpp"

// #include <omp.h>

int main(int argc, char* argv[]) // parsing... later
{
//	omp_set_num_threads(10);

	auto black = std::make_shared<ConstantTexture>(Color{0});
	auto white = std::make_shared<ConstantTexture>(Color{1});
	auto gray1 = std::make_shared<ConstantTexture>(Color{0.25});
	auto gray2 = std::make_shared<ConstantTexture>(Color{0.5});
	auto gray3 = std::make_shared<ConstantTexture>(Color{0.75});
	auto red = std::make_shared<ConstantTexture>(rgb(203, 74, 67));
	auto orange = std::make_shared<ConstantTexture>(rgb(221, 147, 73));
	auto yellow = std::make_shared<ConstantTexture>(rgb(214, 189, 65));
	auto green = std::make_shared<ConstantTexture>(rgb(98, 188, 90));
	auto turquoise = std::make_shared<ConstantTexture>(rgb(89, 195, 148));
	auto lightblue = std::make_shared<ConstantTexture>(rgb(89, 181, 195));
	auto darkblue = std::make_shared<ConstantTexture>(rgb(83, 107, 186));
	auto purple = std::make_shared<ConstantTexture>(rgb(122, 73, 186));
	auto magenta = std::make_shared<ConstantTexture>(rgb(186, 73, 186));

	auto diffBlack = std::make_shared<LambertianMaterial>(black);
	auto diffWhite = std::make_shared<LambertianMaterial>(white);
	auto diffGray1 = std::make_shared<LambertianMaterial>(gray1);
	auto diffGray2 = std::make_shared<LambertianMaterial>(gray2);
	auto diffGray3 = std::make_shared<LambertianMaterial>(gray3);
	auto diffRed = std::make_shared<LambertianMaterial>(red);
	auto diffOrange = std::make_shared<LambertianMaterial>(orange);
	auto diffYellow = std::make_shared<LambertianMaterial>(yellow);
	auto diffGreen = std::make_shared<LambertianMaterial>(green);
	auto diffTurquoise = std::make_shared<LambertianMaterial>(turquoise);
	auto diffLightblue = std::make_shared<LambertianMaterial>(lightblue);
	auto diffDarkblue = std::make_shared<LambertianMaterial>(darkblue);
	auto diffPurple = std::make_shared<LambertianMaterial>(purple);
	auto diffMagenta = std::make_shared<LambertianMaterial>(magenta);
	
	std::vector<std::shared_ptr<LambertianMaterial>> diffuseMaterials {
		diffRed, diffOrange, diffYellow, diffGreen, diffTurquoise, diffDarkblue, diffPurple
	};



	constexpr int iWidth = 480; // 3 : 4
	constexpr int iHeight = 320;
	auto img = std::make_shared<Image>(iWidth, iHeight);


	auto checker = std::make_shared<CheckerTexture>(gray2, gray3, true, 2.5);
	auto diffChecker = std::make_shared<LambertianMaterial>(checker);
	auto glass = std::make_shared<DielectricMaterial>(1.49);

	auto scene = std::make_shared<HittableList>();

	
	auto floor = std::make_shared<Plane>(Vector{0, 1, 0}, 0, diffChecker);
	scene->add(floor);//, std::make_shared<Plane>(Vector{0, -1, 0}, 0.6, glass));

	// center hollow glass sphere
	constexpr double rs0 = 3;
	auto s0out = std::make_shared<Sphere>(Point{0, rs0, 0}, rs0, glass);
	auto s0in = std::make_shared<Sphere>(Point{0, rs0, 0}, .2 - rs0, glass);
	scene->add(s0out, s0in);

	// spheres around center
	constexpr double r = 1;
	constexpr double dist = 7;
	constexpr double theta0 = -140_deg;
	constexpr int n = 7;
	constexpr double dtheta = 360_deg / n - 0_deg;
	for (int i = 0; i < n; ++i) {
		const double theta = theta0 + i * dtheta;
		const double spherex = dist * std::cos(theta);
		const double spherey = dist * std::sin(theta);
		auto sphere = std::make_shared<Sphere>(Point{spherex, r, spherey}, r, diffuseMaterials[i]);
		scene->add(sphere);
	}

	//scene->add(std::make_shared<Sphere>(Point{0, 2, 0}, 2, glass));
	auto camera = std::make_shared<PerspectiveCamera>(
		rayFromTo(Point{8, 4.5, -11}, Point{0, 2, 0}),
		Vector{0, 1, 0},
		65_deg,
		iWidth, iHeight,
		0,
		5
	);

	auto renderer = std::make_shared<Renderer>(img);

	renderer->render(camera, scene, 3);
	img->writeToPNG("output.png");
}
