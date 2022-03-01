#include <cmath>
#include "../math/vector.hpp"
#include "../math/ray.hpp"
#include "../math/random.hpp"
#include "perspective.hpp"




PerspectiveCamera::PerspectiveCamera(
	const Ray&    _eye,
	const Vector& _up,
	const double  _fovDeg,
	const double  _aspectRatio,
	const double  _aperture,
	const double  _focalDistance
)
{
	double fovRad = _fovDeg * 3.14159265358979311600 / 180.0;
	double halfHeight = std::tan(fovRad / 2.0);
	double height = 2.0 * halfHeight;
	double width = _aspectRatio * height;

	z = -normalize(_eye.direction);
	x = normalize(cross(_up, z));
	y = cross(z, x);

	position = _eye.origin;
	viewportRight = _focalDistance * width * x;
	viewportUp = _focalDistance * height * y;
	viewportOrigin = position - viewportRight / 2.0 - viewportUp / 2.0 - _focalDistance * z;

	lensRadius = _aperture / 2.0;
}

Ray PerspectiveCamera::getRay(const double u, const double v) const
{
	Vector random = lensRadius * randomVectorInXYDisk();
	Vector offset = x * random.x + y * random.y;
	return Ray{
		position + offset,
		viewportOrigin + u * viewportRight + v * viewportUp - position - offset
	};
}
