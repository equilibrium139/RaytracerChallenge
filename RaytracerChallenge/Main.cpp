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

void tick(const Environment& environment, Projectile& projectile)
{
	projectile.position += projectile.velocity;
	projectile.velocity += environment.gravity + environment.wind;
}

int main()
{
	Projectile p{ Point(0, 1, 0), Vector(5, 5, 0) };
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
	ofs << fileContents;
}