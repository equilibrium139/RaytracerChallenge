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

	/*Point p(1.0f, 0.0f, 1.0f);
	p = RotationX(Radians(90.0f)) * p; 
	p = Scaling(5.0f, 5.0f, 5.0f) * p;
	p = Translation(15.0f, 0.0f, 7.)
	total = total * Translation(15.0f, 0.0f, 7.0f);
	std::cout << total << '\n';*/

	Canvas c(400, 400);
	Point hour(1.0f, 0.0f, 0.0f);
	float rotationDegrees = 0.0f;
	const float radius = 400.0f * (3.0f / 8.0f);
	std::cout << radius << '\n';
	for (int i = 0; i < 12; ++i)
	{
		auto point = Translation(200.0f, 200.0f, 0.0f) * Scaling(radius, radius, 1.0f) * 
			RotationZ(Radians(rotationDegrees)) * hour;
		// std::cout << point.x << '\t' << point.y << '\n';
		c.PutPixel((int)point.x, (int)point.y, Color(1.0f, 1.0f, 1.0f));
		rotationDegrees += 30.0f;
	}

	auto fileContents = CanvasToPPM(c);
	std::ofstream ofs("test.ppm");
	ofs << fileContents;
}