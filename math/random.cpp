#include <cmath>
#include <random>
#include "random.hpp"
#include "vector.hpp"



double randomDouble()
{  
	static std::uniform_real_distribution<double> dist{ 0.0, 1.0 };
	static std::mt19937 gen{ std::random_device{}() };
	return dist(gen);
}

double randomDouble(const double min, const double max)
{
	return randomDouble() * (max - min) + min;
}

Vector randomVectorInSphere()
{
	Vector random;
	do
	{
		random = 2.0 * Vector(
			randomDouble() - 0.5, randomDouble() - 0.5, randomDouble() - 0.5
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
			randomDouble() - 0.5, randomDouble() - 0.5, randomDouble() - 0.5
		);
	}
	while(length2(direction) <= 1e-8 || length2(direction) >= 1);
	return normalize(direction);
}

Vector randomVectorInHemisphere(const Vector& normal)
{
	Vector random = randomVectorInSphere();
	return dot(random, normal) > 0.0 ? random : -random;
}

Vector randomVectorInXYDisk()
{
	Vector random;
	do
	{
		random = 2.0 * Vector(
			randomDouble() - 0.5, randomDouble() - 0.5, 0.0
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
			randomDouble() - 0.5, randomDouble() - 0.5, 0.0
		);
	}
	while(length2(direction) <= 1e-8 || length2(direction) >= 1);
	return direction;
}
