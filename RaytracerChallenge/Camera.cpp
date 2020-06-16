#include "Camera.h"

Camera::Camera(int hsz, int vsz, float fieldOfView, Mat4 trans)
	:hsize(hsz), vsize(vsz), fov(fieldOfView), transform(trans)
{
	float halfView = std::tan(fov / 2.0f);
	float aspect = (float)hsize / (float)vsize;
	if (aspect > 1.0f)
	{
		halfWidth = halfView;
		halfHeight = halfView / aspect;
	}
	else
	{
		halfWidth = halfView * aspect;
		halfHeight = halfView;
	}
	pixelSize = (halfWidth * 2.0f) / hsize;
}

Ray RayForPixel(const Camera& c, int px, int py)
{
	float xOffset = (px + 0.5f) * c.pixelSize;
	float yOffset = (py + 0.5f) * c.pixelSize;

	float worldX = c.halfWidth - xOffset;
	float worldY = c.halfHeight - yOffset;

	Point pixel = c.transform.Inverse().value() * Point(worldX, worldY, -1.0f);
	Point origin = c.transform.Inverse().value() * Point(0.0f, 0.0f, 0.0f);
	return
	{
		origin,
		Normalize(pixel - origin)
	};
}

Canvas Render(const Camera& c, const World& w)
{
	Canvas image(c.hsize, c.vsize);
	for (int y = 0; y < c.vsize; ++y)
	{
		for (int x = 0; x < c.hsize; ++x)
		{
			Ray ray = RayForPixel(c, x, y);
			image.PutPixel(x, y, ColorAt(w, ray));
		}
	}
	return image;
}