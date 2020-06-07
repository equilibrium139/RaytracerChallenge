#pragma once

#include <algorithm>
#include <memory>
#include <optional>

#include "Intersection.h"
#include "Matrix.h"
#include "Vector.h"
#include "Point.h"
#include "Sphere.h"

struct Ray
{
	Point origin;
	Vector direction;
	Intersection hit;
	Point Position(float t) { return origin + direction * t; }
	std::pair<std::optional<Intersection>, std::optional<Intersection>> Intersect(const Sphere& s);
};

inline Ray Transform(const Mat4& transform, const Ray& ray)
{
	return {
		Point(transform * ray.origin),
		Vector(transform * ray.direction)
	};
}