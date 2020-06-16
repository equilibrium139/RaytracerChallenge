#include "Sphere.h"



Vector Sphere::NormalAt(Point p) const
{
	Point objectPoint = transform.Inverse().value() * p;
	Vector objectNormal = objectPoint - Point(0.0f, 0.0f, 0.0f);
	Vector worldNormal = transform.Inverse().value().GetTransposed() * objectNormal;
	return Normalize(worldNormal);
}
