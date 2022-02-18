#include <cmath>
#include "../math/random.hpp"
#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "perspective.hpp"




PerspectiveCamera::PerspectiveCamera(Point _lookfrom, Point _lookat, Vector _up, double _fovDeg, double _aspectRatio, double _aperture, double _focalDistance)
{
	double fovRad = _fovDeg * 3.14159265358979311600 / 180.0;
	double halfHeight = std::tan(fovRad / 2.0);
	double height = 2.0 * halfHeight;
	double width = _aspectRatio * height;

	z = normalize(_lookfrom - _lookat);
	x = normalize(cross(_up, z));
	y = cross(z, x);

	position = _lookfrom;
	viewportRight = _focalDistance * width * x;
	viewportUp = _focalDistance * height * y;
	viewportOrigin = position - viewportRight / 2.0 - viewportUp / 2.0 - _focalDistance * z;

	lensRadius = _aperture / 2.0;
}

Ray PerspectiveCamera::getRay(double u, double v) const
{
	Vector random = lensRadius * randomVectorInXYDisk();
	Vector offset = x * random.x + y * random.y;
	return Ray(
		position + offset,
		viewportOrigin + u * viewportRight + v * viewportUp - position - offset
	);
}
