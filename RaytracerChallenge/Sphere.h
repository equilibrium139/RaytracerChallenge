#pragma once

#include "Matrix.h"
#include "Material.h"

struct Sphere
{
	Mat4 transform = Mat4::Identity();
	Material mat;
	Vector NormalAt(Point p);
	bool operator==(const Sphere& rhs) const
	{
		return mat == rhs.mat && transform == rhs.transform;
	}
	bool operator!=(const Sphere& rhs) const
	{
		return !(*this == rhs);
	}
};
