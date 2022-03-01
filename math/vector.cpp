#include <cmath>
#include <iostream>
#include "vector.hpp"



Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(const double _x) : x(_x), y(_x), z(_x) {}

Vector::Vector(const double _x, const double _y, const double _z) : x(_x), y(_y), z(_z) {}



Vector Vector::operator + (const Vector& v) const
{
	return Vector( x + v.x, y + v.y, z + v.z );
}

Vector& Vector::operator += (const Vector& v)
{
	x += v.x, y += v.y, z += v.z; return *this;
}

Vector Vector::operator - (const Vector& v) const
{
	return Vector( x - v.x, y - v.y, z - v.z );
}

Vector& Vector::operator -= (const Vector &v)
{
	x -= v.x, y -= v.y, z -= v.z; return *this;
}

Vector Vector::operator + () const
{
	return Vector( +x, +y, +z );
}

Vector Vector::operator - () const
{
	return Vector( -x, -y, -z );
}

Vector Vector::operator * (const double s) const
{
	return Vector( x * s, y * s, z * s );
}

Vector& Vector::operator *= (const double s)
{
	x *= s, y *= s, z *= s; return *this;
}

Vector Vector::operator / (const double s) const
{
	return Vector( x / s, y / s, z / s );
}

Vector& Vector::operator /= (const double s)
{
	x /= s, y /= s, z /= s; return *this;
}

Vector Vector::operator * (const Vector& v) const
{
	return Vector( x * v.x, y * v.y, z * v.z );
}

Vector& Vector::operator *= (const Vector& v)
{
	x *= v.x, y *= v.y, z *= v.z; return *this;
}

Vector Vector::operator / (const Vector& v) const
{
	return Vector( x / v.x, y / v.y, z / v.z );
}

Vector& Vector::operator /= (const Vector& v)
{
	x /= v.x, y /= v.y, z /= v.z; return *this;
}

Vector Vector::inverse() const
{
	return Vector( 1.0 / x, 1.0 / y, 1.0 / z );
}

double dot(const Vector& a, const Vector& b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

double Vector::operator | (const Vector& v) const
{
	return dot(*this, v);
}

Vector cross(const Vector& a, const Vector& b)
{
	return Vector( a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x );
}

Vector Vector::operator ^ (const Vector& v) const
{
	return cross(*this, v);
}

bool Vector::operator == (const Vector& v) const
{
	return x==v.x && y==v.y && z==v.z;
}

bool Vector::operator != (const Vector& v) const
{
	return !(x==v.x && y==v.y && z==v.z);
}

double length2(const Vector& v)
{
	return v.x*v.x + v.y*v.y + v.z*v.z;
}

double length(const Vector& v)
{
	return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

Vector normalize(const Vector& v)
{
	double len2 = length2(v);
	if (len2 > 0.0) {
		return v * (1.0/std::sqrt(len2));
	}
	return v;
}

Vector& Vector::normalize()
{
	double len2 = length2(*this);
	if (len2 > 0.0) {
		(*this) *= 1.0/std::sqrt(len2);
	}
	return *this;
}

Vector lerp(const Vector& start, const Vector& end, const double t)
{
	return start * (1-t) + end * t;
}

const double& Vector::operator [] (const uint8_t i) const
{
	return (&x)[i];
}

double& Vector::operator [] (const uint8_t i)
{
	return (&x)[i];
}

std::ostream& operator << (std::ostream &os, const Vector& v)
{
	os << "Vector{" << v.x << ", " << v.y << ", " << v.z << "}";
	return os;
}
