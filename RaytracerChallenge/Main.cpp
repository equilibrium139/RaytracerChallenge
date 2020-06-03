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
	Mat4 m; 
	m(0, 0) = 8.0f;
	m(0, 1) = -5.0f;
	m(0, 2) = 9.0f;
	m(0, 3) = 2.0f;

	m(1, 0) = 7.0f;
	m(1, 1) = 5.0f;
	m(1, 2) = 6.0f;
	m(1, 3) = 1.0f;

	m(2, 0) = -6.0f;
	m(2, 1) = 0.0f;
	m(2, 2) = 9.0f;
	m(2, 3) = 6.0f;

	m(3, 0) = -3.0f;
	m(3, 1) = 0.0f;
	m(3, 2) = -9.0f;
	m(3, 3) = -4.0f;

	auto inverse = m.Inverse();
	for (std::size_t i = 0; i < 4; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
		{
			std::cout << inverse.second(i, j) << '\t';
		}
		std::cout << '\n';
	}

	std::cout << m.Determinant() << '\n';
}