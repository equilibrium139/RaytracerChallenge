#include "Color.h"

Color& Color::operator+=(const Color& other)
{
	r += other.r;
	g += other.g;
	b += other.b;
	return *this;
}

Color& Color::operator-=(const Color& other)
{
	r -= other.r;
	g -= other.g;
	b -= other.b;
	return *this;
}

Color& Color::operator*=(float scalar)
{
	r *= scalar;
	g *= scalar;
	b *= scalar;
	return *this;
}

Color& Color::operator*=(const Color& other)
{
	r *= other.r;
	g *= other.g;
	b *= other.b;
	return *this;
}