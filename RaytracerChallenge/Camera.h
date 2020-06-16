#pragma once

#include "Canvas.h"
#include "Matrix.h"
#include "Ray.h"
#include "World.h"

struct Camera
{
	Camera(int hsz, int vsz, float fieldOfView, Mat4 trans = Mat4::Identity());
	Mat4 transform = Mat4::Identity();
	int hsize;
	int vsize;
	float fov;
	float pixelSize;
	float halfWidth;
	float halfHeight;
};

Ray RayForPixel(const Camera& c, int px, int py);
Canvas Render(const Camera& c, const World& w);