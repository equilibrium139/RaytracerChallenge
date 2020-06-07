#include "Ray.h"

std::pair<std::optional<Intersection>, std::optional<Intersection>> Ray::Intersect(const Sphere& s)
{
	Ray transformed = Transform(s.transform.Inverse().value(), *this);
	Vector sphereToRay = transformed.origin - Point(0.0f, 0.0f, 0.0f);
	float a = Dot(transformed.direction, transformed.direction);
	float b = 2 * Dot(transformed.direction, sphereToRay);
	float c = Dot(sphereToRay, sphereToRay) - 1.0f;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0.0f)
	{
		return { {}, {} };
	}
	else
	{
		float t1 = (-b - std::sqrt(discriminant)) / 2 * a;
		float t2 = (-b + std::sqrt(discriminant)) / 2 * a;

		return std::minmax(std::optional<Intersection>({ s, t1 }),
			std::optional<Intersection>({ s, t1 }));
	}
}
