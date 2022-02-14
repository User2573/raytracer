#include <cmath>
#include <random>
#include "random.hpp"
#include "vector.hpp"



void initializeRandom()
{
	random01.init();
}

Vector randomVectorInSphere()
{
	Vector direction;
	do
	{
		direction = 2.0 * Vector(
			random01() - 0.5, random01() - 0.5, random01() - 0.5
		);
	}
	while (length2(direction) >= 1.0);
	return direction;
}

Vector randomUnitVector()
{
	Vector direction;
	do
	{
		direction = 2.0 * Vector(
			random01() - 0.5, random01() - 0.5, random01() - 0.5
		);
	}
	while (1e-8 > length2(direction) && length2(direction) >= 1.0);
	return normalize(direction);
}
