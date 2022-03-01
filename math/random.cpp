#include <cmath>
#include <random>
#include "random.hpp"
#include "vector.hpp"



Vector randomVectorInSphere()
{
	Vector random;
	do
	{
		random = 2.0 * Vector(
			random01() - 0.5, random01() - 0.5, random01() - 0.5
		);
	}
	while (length2(random) >= 1.0);
	return random;
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
	while(length2(direction) <= 1e-8 || length2(direction) >= 1);
	return normalize(direction);
}

Vector randomVectorInXYDisk()
{
	Vector random;
	do
	{
		random = 2.0 * Vector(
			random01() - 0.5, random01() - 0.5, 0
		);
	}
	while(length2(random) >= 1);
	return random;
}

Vector randomUnitXYVector()
{
	Vector direction;
	do
	{
		direction = 2.0 * Vector(
			random01() - 0.5, random01() - 0.2, 0
		);
	}
	while(length2(direction) <= 1e-8 || length2(direction) >= 1);
	return direction;
}
