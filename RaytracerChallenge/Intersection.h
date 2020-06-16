#pragma once

#include "Sphere.h"

#include <vector>

struct Ray;

struct Intersection
{
	const Sphere* object;
	float t;
	Intersection(const Sphere* obj, float t) 
		:object(obj), t(t) {}
	bool operator==(const Intersection& rhs) const
	{
		return *object == *(rhs.object) && Equals(t, rhs.t);
	}
	bool operator!=(const Intersection& rhs) const
	{
		return !(*this == rhs);
	}
};

bool operator<(const Intersection& lhs, const Intersection& rhs);

Intersection Hit(const std::vector<Intersection>& vec);

// Prepare intersection
struct IntersectionData
{
	const Sphere* object;
	Point point;
	Point overPoint;
	Vector eyeVec;
	Vector normal;
	float t;
	bool inside;
	IntersectionData(const Intersection& i, const Ray& ray);
private:
	// epsilon in MathUtilities.h doesn't work, needs to be larger
	static float overPointEpsilon() {
		return 0.01f;
	};
};