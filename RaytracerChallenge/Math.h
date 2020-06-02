#pragma once

#include <cmath>

const float EPSILON = 0.0001f;

inline bool Equals(float a, float b, float e = EPSILON)
{
	return std::abs(a - b) < e;
}