#pragma once

#include <memory>
#include "../math/vector.hpp"
#include "../hittable/hitrecord.hpp"
#include "texture.hpp"



// still an abstract class: checker can be in 2d or 3d
class CheckerTexture : public Texture
{
	std::shared_ptr<Texture> evenTexture;
	std::shared_ptr<Texture> oddTexture;
public:
	bool is2D;
private:
	double halfInvScale;



	bool evenOdd(const double x) const;

public:
	CheckerTexture();

	CheckerTexture(
		const std::shared_ptr<Texture> _evenTexture, const std::shared_ptr<Texture> _oddTexture,
		const bool _is2D = true, const double _scale = 1
	);



	void setScale(const double scale);

	Color value(const HitRecord& record) const override;
};
