#pragma once

#include "Color.h"
#include "Material.h"
#include "Point.h"
#include "Vector.h"
#include "PointLight.h"
#include "World.h"
#include "Intersection.h"

Color Lighting(const Material& mat, const Point& point, const PointLight& light, const Vector& eye,
	const Vector& normal, bool inLighting = false);

Color ShadeHit(const World& w, const IntersectionData& d);