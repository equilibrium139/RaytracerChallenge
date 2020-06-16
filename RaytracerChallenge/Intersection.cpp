#include "Intersection.h"
#include "Ray.h"
#include <algorithm>

Intersection Hit(const std::vector<Intersection>& vec)
{
	Intersection min = *std::min_element(vec.begin(), vec.end(), 
		[](const auto& lhs, const auto& rhs)
		{
			if (rhs.t < 0.0f || lhs.t < 0.0f)
			{
				return lhs.t > rhs.t;
			}
			return lhs.t < rhs.t;
		});
	return min;
}

bool operator<(const Intersection& lhs, const Intersection& rhs)
{
	return lhs.t < rhs.t;
}

IntersectionData::IntersectionData(const Intersection& i, const Ray& ray)
	:object(i.object), point(ray.Position(i.t)), eyeVec(-ray.direction), 
	normal(object->NormalAt(point)), t(i.t)
{
	if (Dot(normal, eyeVec) < 0)
	{
		inside = true;
		normal = -normal;
	}
	else
	{
		inside = false;
	}
	overPoint = point + (normal * overPointEpsilon());
}