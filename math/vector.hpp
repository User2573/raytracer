#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

#define VECTOR_HPP_USE_ANONYMOUS_STRUCTS



class Vector
{
public:
#ifdef VECTOR_HPP_USE_ANONYMOUS_STRUCTS
	union {
		struct {
			double r, g, b;
		};
		struct {
			double x, y, z;
		};
	};
#else
	double x, y, z;
	double r, g, b;
#endif



	Vector();

	Vector(const double _x);

	Vector(const double _x, const double _y, const double _z);



	Vector operator + (const Vector& v) const;

	Vector& operator += (const Vector& v);

	Vector operator - (const Vector& v) const;

	Vector& operator -= (const Vector& v);

	Vector operator + () const;

	Vector operator - () const;

	Vector operator * (const double s) const;

	Vector& operator *= (const double s);

	Vector operator / (const double s) const;

	Vector& operator /= (const double s);

	Vector operator * (const Vector& v) const;

	Vector& operator *= (const Vector& v);

	Vector operator / (const Vector& v) const;

	Vector& operator /= (const Vector& v);

	Vector inverse() const;

	double operator | (const Vector& v) const;

	Vector operator ^ (const Vector& v) const;

	bool operator == (const Vector& v) const;

	bool operator != (const Vector& v) const;

	Vector& normalize();



	const double& operator [] (const uint8_t i) const;

	double& operator [] (const uint8_t i);

	friend std::ostream& operator << (std::ostream &os, const Vector& v);
};



inline Vector operator * (double s, Vector v)
{
	return v * s;
}

double dot(const Vector& a, const Vector& b);

Vector cross(const Vector& a, const Vector& b);

double length2(const Vector& v);

double length(const Vector& v);

Vector normalize(const Vector& v);

inline Vector lerp(Vector start, Vector end, double t)
{
	return start*(1-t) + end*t;
}



typedef Vector Point;
typedef Vector Color;



#endif
