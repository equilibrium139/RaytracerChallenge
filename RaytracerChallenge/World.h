#pragma once

#include "PointLight.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Ray.h"
#include <vector>

struct World
{
	PointLight light{ Point(-10.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f) };
	std::vector<Sphere> spheres{
		Sphere{Mat4::Identity(), Material{Color(0.8f, 1.0f, 0.6f), 0.1f, 0.7f, 0.2f}},
		Sphere{ Scaling(0.5f, 0.5f, 0.5f)}
	};	
};

std::vector<Intersection> IntersectWorld(const World& world, const Ray& ray);
Color ColorAt(const World& w, const Ray& ray);
bool IsShadowed(const World& w, const Point& p);
bool DoesIntersectBeforeLight(const World& w, const Ray& ray);