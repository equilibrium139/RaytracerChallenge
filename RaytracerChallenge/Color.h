#pragma once

#include "MathUtilities.h"

struct Color
{
	Color()
		:r(0.0f), g(0.0f), b(0.0f) {}
	Color(float r, float g, float b)
		:r(r), g(g), b(b) {}
	Color& operator+=(const Color& other);
	Color& operator-=(const Color& other);
	Color& operator*=(float scalar);
	Color& operator*=(const Color& other);
	float r, g, b;
};

inline bool operator==(const Color& lhs, const Color& rhs)
{
	return Equals(lhs.r, rhs.r) && Equals(lhs.g, rhs.g) && Equals(lhs.b, rhs.b);
}

inline Color operator+(Color lhs, const Color& rhs)
{
	lhs += rhs;
	return lhs;
}

inline Color operator-(Color lhs, const Color& rhs)
{
	lhs -= rhs;
	return lhs;
}

inline Color operator*(Color lhs, float rhs)
{
	lhs *= rhs;
	return lhs;
}

inline Color operator*(Color lhs, const Color& rhs)
{
	lhs *= rhs;
	return lhs;
}