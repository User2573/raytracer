#pragma once
#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include "vector.hpp"



void initializeRandom();

class
{
	std::uniform_real_distribution<double> dist{ 0.0, 1.0 };
	std::mt19937 gen{ std::random_device{}() };

public:
  double operator () ()
  {
	  return dist(gen);
  }
} random01;

Vector randomVectorInSphere();

Vector randomUnitVector();



#endif
