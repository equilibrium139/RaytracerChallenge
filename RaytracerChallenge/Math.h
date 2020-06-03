#pragma once

#include <cmath>

const float EPSILON = 0.0001f;

inline bool Equals(float a, float b)
{
	return std::abs(a - b) < EPSILON;
}