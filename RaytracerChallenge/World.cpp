#include "World.h"
#include "Lighting.h"

std::vector<Intersection> IntersectWorld(const World& world, const Ray& ray)
{
	auto& spheres = world.spheres;
	std::vector<Intersection> intersections;
	for (auto& sphere : spheres)
	{
		auto intersection = ray.Intersect(sphere);
		if (intersection.first.has_value())
		{
			intersections.push_back(intersection.first.value());
			intersections.push_back(intersection.second.value());
		}
	}
	std::sort(intersections.begin(), intersections.end());
	return intersections;
}

Color ColorAt(const World& w, const Ray& ray)
{
	auto intersections = IntersectWorld(w, ray);
	if (intersections.empty())
	{
		return Color(0.0f, 0.0f, 0.0f);
	}
	auto hit = Hit(intersections);
	IntersectionData id(hit, ray);
	return ShadeHit(w, id);
}

bool IsShadowed(const World& w, const Point& p)
{
	Ray ray{ p, Normalize(w.light.position - p) };
	float distanceToLight = (w.light.position - p).Magnitude();
	auto intersections = IntersectWorld(w, ray);
	if (intersections.empty())
	{
		return false;
	}
	auto hit = Hit(intersections);
	float distanceToHit = (ray.Position(hit.t) - ray.origin).Magnitude();
	return hit.t > 0.0f && hit.t < distanceToLight;
	
	//return DoesIntersectBeforeLight(w, ray);
}

bool DoesIntersectBeforeLight(const World& w, const Ray& ray)
{
	/*const auto& spheres = w.spheres;
	float distanceToLight = (w.light.position - ray.origin).Magnitude();
	for (auto& sphere : spheres)
	{
		auto intersection = ray.Intersect(sphere);
		if (intersection.first.has_value() && (intersection.first.value().t > 0.0f || 
											   intersection.second.value().t > 0.0f))
		{
			auto firstT = intersection.first.value().t;
			auto secondT = intersection.second.value().t;
			if (firstT > 0.0f)
			{
				float distanceToIntersection = (ray.Position(firstT) 
												- ray.origin).Magnitude();
				if (distanceToIntersection < distanceToLight)
				{
					return true;
				}
			}
			else if(secondT > 0.0f)
			{
				float distanceToIntersection = (ray.Position(secondT)
					- ray.origin).Magnitude();
				if (distanceToIntersection < distanceToLight)
				{
					return true;
				}
			}
		}
	}
	return false;*/
}
