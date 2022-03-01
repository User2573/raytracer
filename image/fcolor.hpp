#pragma once

#include <iostream>
#include "../math/vector.hpp"



class FColor
{
public:
	unsigned char r, g, b;



	FColor();

	FColor(const unsigned char _x);

	FColor(const unsigned char _r, const unsigned char _g, const unsigned char _b);

	FColor(const Vector& _v);



	friend std::ostream& operator << (std::ostream& os, const FColor& color);
};
