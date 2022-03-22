#include <cmath>
#include <memory>
#include"../math/vector.hpp"
#include "../hittable/hitrecord.hpp"
#include "constant.hpp"
#include "checker.hpp"



CheckerTexture::CheckerTexture()
: CheckerTexture(std::make_shared<ConstantTexture>(Color{0}), std::make_shared<ConstantTexture>(Color{1})) {}

CheckerTexture::CheckerTexture(
	const std::shared_ptr<Texture> _evenTexture, const std::shared_ptr<Texture> _oddTexture,
	const bool _is2D, const double _scale
) : evenTexture(_evenTexture), oddTexture(_oddTexture), is2D(_is2D), halfInvScale(0.5 / _scale) {}



bool CheckerTexture::evenOdd(const double x) const
{
	static auto frac = [](const double x1) -> double {
		return x1 - std::floor(x1);
	};
	return 0.5 < frac(x * halfInvScale);
}

void CheckerTexture::setScale(const double scale)
{
	halfInvScale = 0.5 / scale;
}

Color CheckerTexture::value(const HitRecord& record) const
{
	bool odd = false;
	if (is2D) {
		odd = evenOdd(record.u) != evenOdd(record.v);
	} else {
		// xy plane as uv, invert value if z isn't even
		double z = evenOdd(record.point.z);
		odd = evenOdd(record.point.x) != evenOdd(record.point.y);
		odd = z ? !odd : odd;
	}

	if (odd) {
		return oddTexture->value(record);
	} else {
		return evenTexture->value(record);
	}
}
