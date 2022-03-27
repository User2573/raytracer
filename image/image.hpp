#pragma once

#include <functional>
#include <ranges>
#include <string>
#include <vector>
#include "../math/vector.hpp"
#include "pixel.hpp"



class Image
{
protected:
	std::vector<Pixel> data;

public:
	const int width, height;

public:
	Image();

	Image(const int _side);

	Image(const int _width, const int _height);



	// access pixel at position
	const Color& operator () (const int x, const int y) const;

	Color& operator () (const int x, const int y);

	void for_each(const std::function<Color(Color, int, int)>& lambda);

	void writeToPPM(const char* filename) const;

	void writeToPNG(const char* filename) const;

	// print image... why tho
	std::string str() const;
};
