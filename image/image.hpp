#pragma once
#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <functional>
#include <string>
#include <vector>
#include "../math/vector.hpp"


class Image
{
protected:
	std::vector<Color> data;

public:
	const int width, height;

	Image();

	Image(int _side);

	Image(int _width, int _height);



	const Color& operator () (int x, int y) const;

	Color& operator () (int x, int y);



	void for_each(std::function<void(Color&, int, int)> lambda);

	void writeToPPM(const char* filename) const;

	void writeToPNG(const char* filename) const;

	// print image... why tho
	std::string str() const;
};



#endif
