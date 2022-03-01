#include "math/ray.hpp"
#include "renderer.hpp"
#include "image/image.hpp"
#include "camera/perspective.hpp"
#include "hittable/hitrecord.hpp"
#include "hittable/sphere.hpp"

int main()
{
	constexpr int iWidth = 256;
	constexpr int iHeight = 256;
	constexpr double ratio = double(iHeight) / iWidth;
	Image img{iWidth, iHeight};

	PerspectiveCamera camera{
		rayFromTo({0, 0, 0}, {0, 0, -1}), // camera eye
		{0, 1, 0}, // up vector, do not change
		60, // fov in degrees
		ratio, // aspect ratio
		0, // aperture (how blurry)
		5 // focus dist.
	};

	Renderer renderer{&img};

	Sphere s1{{0, 0, -3}, 1};

	renderer.render(&camera, &s1);
	img.writeToPNG("output.png");
}
