#pragma once

#include "Color.h"
#include "Material.h"
#include "Point.h"
#include "Vector.h"
#include "PointLight.h"

Color Lighting(const Material& mat, const Point& point, const PointLight& light, const Vector& eye, const Vector& normal);