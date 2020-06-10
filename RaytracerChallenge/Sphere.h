#pragma once

#include "Matrix.h"
#include "Material.h"

struct Sphere
{
	Mat4 transform = Mat4::Identity();
	Material mat;
	Vector NormalAt(Point p);
};

inline Vector Sphere::NormalAt(Point p)
{
	Point objectPoint = transform.Inverse().value() * p;
	Vector objectNormal = objectPoint - Point(0.0f, 0.0f, 0.0f);
	Vector worldNormal = transform.Inverse().value().Transpose() * objectNormal;
	return Normalize(worldNormal);
}
