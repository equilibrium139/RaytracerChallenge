#pragma once

#include <memory>

#include "Vector.h"
#include "Point.h"
#include "Sphere.h"

struct Ray
{
	Point origin;
	Vector direction;
	Point Position(float t) { return origin + direction * t; }
	std::unique_ptr<float> Intersect(const Sphere& s) {};
};

