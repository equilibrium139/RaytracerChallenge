#include "Point.h"
#include "Vector.h"
#include "Sphere.h"	
#include "Ray.h"
#include "PointLight.h"
#include "Lighting.h"
#include "World.h"
#include "Camera.h"

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

	//Canvas c(400, 400);
	//Point hour(1.0f, 0.0f, 0.0f);
	//float rotationDegrees = 0.0f;
	//const float radius = 400.0f * (3.0f / 8.0f);
	//std::cout << radius << '\n';
	//for (int i = 0; i < 12; ++i)
	//{
	//	auto point = Translation(200.0f, 200.0f, 0.0f) * Scaling(radius, radius, 1.0f) * 
	//		RotationZ(Radians(rotationDegrees)) * hour;
	//	// std::cout << point.x << '\t' << point.y << '\n';
	//	c.PutPixel((int)point.x, (int)point.y, Color(1.0f, 1.0f, 1.0f));
	//	rotationDegrees += 30.0f;
	//}

	//auto fileContents = CanvasToPPM(c);
	//std::ofstream ofs("test.ppm");
	//ofs << fileContents;

	/*Canvas c(400, 400);
	Sphere s;
	s.mat.color = Color(1.0f, 0.2f, 1.0f);
	PointLight light{ Point(-10.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f) };

	Point rayOrigin(0.0f, 0.0f, -10.0f);
	float wallZ = 10.0f;
	float wallSize = 7.0f;
	float pixelSize = wallSize / 400.0f;
	float half = wallSize / 2.0f;
	for (int y = 0; y < c.height; ++y)
	{
		float worldY = half - y * pixelSize;
		for (int x = 0; x < c.width; ++x)
		{
			float worldX = -half + x * pixelSize;
			Point position(worldX, worldY, wallZ);
			Ray ray{ rayOrigin, Normalize(position - rayOrigin) };
			auto intersections = ray.Intersect(s);
			if (intersections.first.has_value())
			{
				Point p = ray.Position(intersections.first.value().t);
				Vector normal = intersections.first.value().object->NormalAt(p);
				Vector eye = -ray.direction;
				Color lighting = Lighting(s.mat, p, light, eye, normal);
				c.PutPixel(x, y, lighting);
			}
		}
	}

	auto fileContents = CanvasToPPM(c);
	std::ofstream ofs("purpleSphere.ppm");
	ofs << fileContents;*/

	World w;
	Sphere floor{ Scaling(10.0f, 0.01f, 10.0f), Material{Color(1.0f, 0.9f, 0.9f), 0.1f, 0.9f, 0.0f} };
	Sphere leftWall{ Translation(0.0f, 0.0f, 5.0f) * RotationY(-PI / 4.0f) * RotationX(PI / 2.0f) *
					Scaling(10.0f, 0.01f, 10.0f), floor.mat };
	Sphere rightWall{ Translation(0.0f, 0.0f, 5.0f) * RotationY(PI / 4.0f) * RotationX(PI / 2.0f) *
					Scaling(10.0f, 0.01f, 10.0f), floor.mat };
	Sphere middle{ Translation(-0.5f, 1.0f, 0.5f), Material{Color(0.1f, 1.0f, 0.5f), 0.1f, 0.7f, 0.3f} };
	Sphere right{ Translation(1.5f, 1.0f, -0.5f) * Scaling(0.5f, 0.5f, 0.5f), Material{Color(0.5f, 1.0f, 0.1f), 0.1f, 0.7f, 0.3f} };
	w.spheres = { floor, leftWall, rightWall, middle, right };
	Camera cam(400, 400, PI / 3.0f, View(Point(0.0f, 1.5f, -5.0f), Point(0.0f, 1.0f, 0.0f), Vector(0.0f, 1.0f, 0.0f)));
	Canvas c = Render(cam, w);
	auto fileContents = CanvasToPPM(c);
	std::ofstream ofs("wallsSpheresShadows3.ppm");
	ofs << fileContents;

	//World w;
	// Ray ray{ Point(0.0f, 0.0f, -5.0f), Vector(0.0f, 0.0f, 1.0f) };
	//auto intersections = IntersectWorld(w, ray);
	//std::cout << intersections[0].second.value().t << '\n';
	/*Sphere s{ Scaling(0.5f, 0.5f, 0.5f), Material{Color(0.8f, 1.0f, 0.6f), 0.1f, 0.7f, 0.2f} };
	auto intersects = ray.Intersect(s);
	std::cout << intersects.second.value().t << '\n';*/
}