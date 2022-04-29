#pragma once

#include "vector.hpp"



double randomDouble();

double randomDouble(const double min, const double max);

Vector randomVectorInSphere();

Vector randomUnitVector();

Vector randomVectorInHemisphere(const Vector& normal);

Vector randomVectorInXYDisk();

Vector randomUnitXYVector();
