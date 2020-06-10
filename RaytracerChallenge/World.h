#pragma once

#include "PointLight.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Ray.h"
#include <vector>

struct World
{
	PointLight light{ Point(-10.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f) };
	Sphere s1{ Mat4::Identity(), Material{Color(0.8f, 1.0f, 0.6f), 0.1f, 0.7f, 0.2f} };
	Sphere s2{ Scaling(0.5f, 0.5f, 0.5f) };
};

inline auto IntersectWorld(const World& world, const Ray& ray)
	->std::vector<std::pair<std::optional<Intersection>, std::optional<Intersection>>>
{
	return {
		ray.Intersect(world.s2),
		ray.Intersect(world.s1)
	};
}