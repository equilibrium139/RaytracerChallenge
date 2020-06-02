#pragma once

#include "Math.h"
#include "Vector.h"

struct Point
{
	Point()
		:x(0), y(0), z(0) {}
	Point(float x, float y, float z)
		:x(x), y(y), z(z) {}
	Point& operator+=(const Vector& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	Point& operator-=(const Vector& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
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