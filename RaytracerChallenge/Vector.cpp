#include "Vector.h"

Vector& Vector::operator+=(const Vector& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector& Vector::operator-=(const Vector& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector& Vector::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector& Vector::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

void Vector::Normalize()
{
	float magnitude = Magnitude();
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}