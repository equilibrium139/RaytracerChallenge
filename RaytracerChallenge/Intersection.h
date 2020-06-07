#pragma once

#include "Sphere.h"

struct Intersection
{
	Sphere object;
	float t;
};

inline bool operator<(const Intersection& lhs, const Intersection& rhs)
{
	return lhs.t < rhs.t;
}