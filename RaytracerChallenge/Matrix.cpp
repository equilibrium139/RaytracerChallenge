#include "Matrix.h"

Mat4 View(const Point& from, const Point& to, const Vector& up)
{
    Vector forward = Normalize(to - from);
    Vector left = Cross(forward, Normalize(up));
    Vector trueUp = Cross(left, forward);
    return Mat4{
        left.x, left.y, left.z, 0.0f,
        trueUp.x, trueUp.y, trueUp.z, 0.0f,
        -forward.x, -forward.y, -forward.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    } * Translation(-from.x, -from.y, -from.z);
}
