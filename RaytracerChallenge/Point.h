#pragma once

#include "MathUtilities.h"
#include "Vector.h"

struct Point
{
	Point()
		:x(0), y(0), z(0) {}
	Point(float x, float y, float z)
		:x(x), y(y), z(z) {}
	Point& operator+=(const Vector& rhs);
	Point& operator-=(const Vector& rhs);
	float x, y, z;
};

inline bool operator==(const Point& lhs, const Point& rhs)
{
	return Equals(lhs.x, rhs.x) && Equals(lhs.y, rhs.y) && Equals(lhs.z, rhs.z);
}

inline Point operator+(Point lhs, const Vector& rhs)
{
	lhs += rhs;
	return lhs;
}

inline Point operator-(Point lhs, const Vector& rhs)
{
	lhs -= rhs;
	return lhs;
}

inline Vector operator-(Point lhs, const Point& rhs)
{
	return Vector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}