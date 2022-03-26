#include <cmath>
#include "vector.hpp"



Vector::Vector() : Vector(0, 0, 0) {}

Vector::Vector(const double _x) : Vector(_x, _x, _x) {}

Vector::Vector(const double _x, const double _y, const double _z)
: x(_x), y(_y), z(_z) {}



Vector& Vector::operator += (const Vector& v)
{
	x += v.x, y += v.y, z += v.z; return *this;
}

Vector& Vector::operator -= (const Vector& v)
{
	x -= v.x, y -= v.y, z -= v.z; return *this;
}

Vector& Vector::operator *= (const Vector& v)
{
	x *= v.x, y *= v.y, z *= v.z; return *this;
}

Vector& Vector::operator /= (const Vector& v)
{
	x /= v.x, y /= v.y, z /= v.z; return *this;
}

Vector& Vector::operator *= (const double s)
{
	x *= s, y *= s, z *= s; return *this;
}

Vector& Vector::operator /= (const double s)
{
	x /= s, y /= s, z /= s; return *this;
}

Vector& Vector::normalize()
{
	return *this = ::normalize(*this);
}

Vector& Vector::invert()
{
	return *this = ::invert(*this);
}



Vector operator + (const Vector& a, const Vector& b)
{
	return Vector{ a.x + b.x, a.y + b.y, a.z + b.z };
}

Vector operator - (const Vector& a, const Vector& b)
{
	return Vector{ a.x - b.x, a.y - b.y, a.z - b.z };
}

Vector operator + (const Vector& v)
{
	return Vector{ +v.x, +v.y, +v.z }; // :c
}

Vector operator - (const Vector& v)
{
	return Vector{ -v.x, -v.y, -v.z };
}

Vector operator * (const Vector& a, const Vector& b)
{
	return Vector{ a.x * b.x, a.y * b.y, a.z * b.z };
}

Vector operator / (const Vector& a, const Vector& b)
{
	return Vector{ a.x / b.x, a.y / b.y, a.z / b.z };
}

Vector operator * (const Vector& v, const double s)
{
	return Vector{ v.x * s, v.y * s, v.z * s };
}

Vector operator / (const Vector& v, const double s)
{
	return Vector{ v.x / s, v.y / s, v.z / s };
}

Vector operator == (const Vector& a, const Vector& b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

Vector operator != (const Vector& a, const Vector& b)
{
	return a.x != b.x || a.y != b.y || a.z != b.z;
}



double dot(const Vector& a, const Vector& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector cross(const Vector& a, const Vector& b)
{
	return Vector{
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
	};
}

double length2(const Vector& v)
{
	return dot(v, v);
}

double length(const Vector& v)
{
	return std::sqrt(length2(v));
}

Vector normalize(const Vector& v)
{
	double len2 = length2(v);
	if (0.0 < len2 && 1e-8 < std::abs(len2 - 1)) {
		return v / std::sqrt(len2);
	}
	return v;
}

Vector invert(const Vector& v)
{
	return Vector{
		(v.x != 0) ? 1 / v.x : v.x,
		(v.y != 0) ? 1 / v.y : v.y,
		(v.z != 0) ? 1 / v.z : v.z
	};
}

Vector lerp(const Vector& start, const Vector& end, const double t)
{
	return (1-t) * start + t * end;
}

Vector rgb(const int r, const int g, const int b)
{
	return Vector{ r / 255.0, g / 255.0, b / 255.0 };
}
