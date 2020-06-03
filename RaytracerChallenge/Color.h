#pragma once

#include "Math.h"

struct Color
{
	Color()
		:r(0.0f), g(0.0f), b(0.0f) {}
	Color(float r, float g, float b)
		:r(r), g(g), b(b) {}
	Color& operator+=(const Color& other)
	{
		r += other.r;
		g += other.g;
		b += other.b;
		return *this;
	}
	Color& operator-=(const Color& other)
	{
		r -= other.r;
		g -= other.g;
		b -= other.b;
		return *this;
	}
	Color& operator*=(float scalar)
	{
		r *= scalar;
		g *= scalar;
		b *= scalar;
		return *this;
	}
	Color& operator*=(const Color& other)
	{
		r *= other.r;
		g *= other.g;
		b *= other.b;
		return *this;
	}
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