#pragma once

#include <cmath>

#include "MathUtilities.h"

struct Vector
{
	Vector()
		:x(0), y(0), z(0) {}
	Vector(float x, float y, float z)
		:x(x), y(y), z(z) {}
	Vector& operator+=(const Vector& rhs);
	Vector& operator-=(const Vector& rhs);
	Vector& operator*=(float scalar);
	Vector& operator/=(float scalar);
	float Magnitude() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}
	void Normalize();
	float x, y, z;
};

inline bool operator==(const Vector& lhs, const Vector& rhs)
{
	return Equals(lhs.x, rhs.x) && Equals(lhs.y, rhs.y) && Equals(lhs.z, rhs.z);
}

inline Vector operator+(Vector lhs, const Vector& rhs)
{
	lhs += rhs;
	return lhs;
}

inline Vector operator-(Vector lhs, const Vector& rhs)
{
	lhs -= rhs;
	return lhs;
}

inline Vector operator-(const Vector& v)
{
	return { -v.x, -v.y, -v.z };
}

inline Vector operator*(Vector v, float scalar)
{
	v *= scalar;
	return v;
}

inline Vector operator/(Vector v, float scalar)
{
	v /= scalar;
	return v;
}

inline float Dot(const Vector& lhs, const Vector& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

inline Vector Cross(const Vector& lhs, const Vector& rhs)
{
	return { lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x };
}

inline Vector Normalize(Vector v)
{
	v.Normalize();
	return v;
}

inline Vector Reflect(const Vector& v, const Vector& n)
{
	auto vParallel = n * Dot(v, n);
	auto vPerp = v - vParallel;
	return -vParallel + vPerp;
}