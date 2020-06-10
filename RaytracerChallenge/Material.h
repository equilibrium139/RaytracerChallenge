#pragma once

#include "Color.h"

struct Material
{
	Color color = Color(1.0f, 1.0f, 1.0f);
	float ambient = 0.1f;
	float diffuse = 0.9f;
	float specular = 0.9f;
	float shininess = 200.0f;
};