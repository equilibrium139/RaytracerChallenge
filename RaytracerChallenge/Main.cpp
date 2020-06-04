#include "Point.h"
#include "Vector.h"

#include <iostream>
#include <fstream>

struct Projectile
{
	Point position;
	Vector velocity;
};

struct Environment
{
	Vector gravity;
	Vector wind;
};

#include "Canvas.h"
#include "Matrix.h"

void tick(const Environment& environment, Projectile& projectile)
{
	projectile.position += projectile.velocity;
	projectile.velocity += environment.gravity + environment.wind;
}

int main()
{
	/*Projectile p{ Point(0, 1, 0), Vector(5, 5, 0) };
	Environment e{ Vector(0, -0.1, 0), Vector(-0.01, 0, 0) };
	Canvas c(900, 550);
	while (p.position.y > 0.0f)
	{
		std::cout << "Projectile position: (" << p.position.x << ", " << p.position.y << ")\n";
		c.PutPixel(p.position.x, 550 - p.position.y, Color(1.0f, 0.0f, 0.0f));
		tick(e, p);
	}
	auto fileContents = CanvasToPPM(c);
	std::ofstream ofs("test.ppm");
	ofs << fileContents;*/

	Mat4 m
	{
		-5, 2, 6, -8,
		1, -5, 1, 8,
		7, 7, -6, -7,
		1, -3, 7, 4
	};

	auto inverse = m.Inverse();
	Mat4 expected
	{
		0.21805f, 0.45113f, 0.24060f, -0.04511f,
		-0.80827f, -1.45677f, -0.44361f, 0.52068f,
		0.07895f, -0.22368f, -0.05263f, 0.19737f,
		-0.52256f, -0.81391f, -0.30075f, 0.30639f
	};

	std::cout << inverse.second << '\n';
	std::cout << expected << '\n';
}