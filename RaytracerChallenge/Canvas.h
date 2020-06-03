#pragma once

#include <vector>
#include <string>
#include "Color.h"

class Canvas
{
public:
	Canvas(int w, int h, const Color& fill = Color(0.0f, 0.0f, 0.0f))
		:width(w), height(h), pixels(width * height, fill) {}
	const auto& GetPixels() const { return pixels; }
	// x and y must be between 0 and (width - 1)/(height - 1)
	void PutPixel(int x, int y, Color c)
	{
		pixels[y * width + x] = c;
	}
	// x and y must be between 0 and (width - 1)/(height - 1)
	const Color& GetPixel(int x, int y) const
	{
		return pixels[y * width + x];
	}
	void Clear(const Color& c)
	{
		std::fill(pixels.begin(), pixels.end(), c);
	}
	const int width, height;
private:
	std::vector<Color> pixels;
};

std::string CanvasToPPM(const Canvas& canvas);
std::string ColorToPPMFormat(const Color& color);