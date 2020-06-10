#pragma once

#include <cmath>

const float EPSILON = 0.0001f;
const float PI = 3.141592653589793f;
const float DEGREES_TO_RADS = PI / 180.0f;

inline bool Equals(float a, float b)
{
	return std::abs(a - b) < EPSILON;
}

inline float Radians(float degrees)
{
	return degrees * DEGREES_TO_RADS;
}