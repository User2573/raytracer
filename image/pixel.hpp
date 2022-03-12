#pragma once

#include <iostream>
#include "../math/vector.hpp"



class Pixel
{
public:
	Color value;
	int x, y;

public:
	Pixel();

	Pixel(const Color& _value);

	Pixel(const Color& _value, const int _x, const int _y);



	friend std::ostream& operator << (std::ostream& os, const Pixel& pixel);
};
