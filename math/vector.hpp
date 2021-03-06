#pragma once

#include <iostream>



class Vector
{
public:
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
	union {
		double array[3];
		struct {
			double r, g, b;
		};
		struct {
			double x, y, z;
		};
	};
#pragma GCC diagnostic pop


	Vector();

	Vector(const double _x);

	Vector(const double _x, const double _y, const double _z);



	Vector& operator += (const Vector& v);

	Vector& operator -= (const Vector& v);

	Vector& operator *= (const Vector& v);

	Vector& operator /= (const Vector& v);

	Vector& operator *= (const double s);

	Vector& operator /= (const double s);

	Vector& normalize();

	Vector& invert();
//	friend std::ostream& operator << (std::ostream &os, const Vector& v);
};



Vector operator + (const Vector& a, const Vector& b);

Vector operator - (const Vector& a, const Vector& b);

Vector operator + (const Vector& v); // useless... but gotta be consistent

Vector operator - (const Vector& v);

Vector operator * (const Vector& a, const Vector& b);

Vector operator / (const Vector& a, const Vector& b);

Vector operator * (const Vector& v, const double s);

Vector operator / (const Vector& v, const double s);

inline Vector operator * (const double s, const Vector& v)
{
	return v * s;
}

double dot(const Vector& a, const Vector& b);

Vector cross(const Vector& a, const Vector& b);

double length2(const Vector& v);

double length(const Vector& v);

Vector normalize(const Vector& v);

Vector invert(const Vector& v);

Vector lerp(const Vector& start, const Vector& end, const double t);

Vector rgb(const int r, const int g, const int b);



using Point = Vector;
using Color = Vector;
