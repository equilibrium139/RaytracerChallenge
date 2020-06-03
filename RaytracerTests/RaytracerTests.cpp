#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../RaytracerChallenge/Vector.h"
#include "../RaytracerChallenge/Point.h"
#include "../RaytracerChallenge/Color.h"
#include "../RaytracerChallenge/Canvas.h"

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<Point>(const Point& p)
			{
				return L"( " + std::to_wstring(p.x) + L", " + std::to_wstring(p.y) + L", " 
					+ std::to_wstring(p.z) + L")";
			}

			template<> static std::wstring ToString<Vector>(const Vector& v)
			{
				return L"{ " + std::to_wstring(v.x) + L", " + std::to_wstring(v.y) + L", "
					+ std::to_wstring(v.z) + L" }";
			}

			template<> static std::wstring ToString<Color>(const Color& c)
			{
				return L"{ " + std::to_wstring(c.r) + L", " + std::to_wstring(c.g) + L", "
					+ std::to_wstring(c.b) + L" }";
			}
		}
	}
}


namespace RaytracerTests
{
	TEST_CLASS(VectorTests)
	{
	public:
		
		TEST_METHOD(VectorCtor)
		{
			Vector v(4.3f, -4.2f, 3.1f);
			Assert::AreEqual(4.3f, v.x);
			Assert::AreEqual(-4.2f, v.y);
			Assert::AreEqual(3.1f, v.z);
		}

		TEST_METHOD(NegateVector)
		{
			Vector v(1, -2, 3);
			Vector negated = -v;
			Assert::AreEqual(Vector( -1, 2, -3 ), negated);
		}

		TEST_METHOD(ScalarMultiplication)
		{
			Vector v(1, -2, 3);
			v *= 3.5f;
			Assert::AreEqual(Vector(3.5f, -7.0f, 10.5f), v);
		}

		TEST_METHOD(ScalarDivision)
		{
			Vector v(1, -2, 3);
			v /= 2.0f;
			Assert::AreEqual(Vector(0.5f, -1.0f, 1.5f), v);
		}

		TEST_METHOD(Magnitude1)
		{
			Vector v(1, 0, 0);
			Assert::AreEqual(1.0f, v.Magnitude());
		}

		TEST_METHOD(Magnitude2)
		{
			Vector v(0, 1, 0);
			Assert::AreEqual(1.0f, v.Magnitude());
		}

		TEST_METHOD(Magnitude3)
		{
			Vector v(0, 0, 1);
			Assert::AreEqual(1.0f, v.Magnitude());
		}

		TEST_METHOD(Magnitude4)
		{
			Vector v(1, 2, 3);
			Assert::AreEqual(std::sqrt(14.0f), v.Magnitude());
		}

		TEST_METHOD(Normalize1)
		{
			Vector v(4, 0, 0);
			v.Normalize();
			Assert::AreEqual(Vector(1, 0, 0), v);
		}

		TEST_METHOD(Normalize2)
		{
			using std::sqrt;
			Vector v(1, 2, 3);
			v.Normalize();
			Assert::AreEqual(Vector(1.0f / sqrt(14.0f), 2.0f / sqrt(14.0f), 3.0f / sqrt(14.0f)), v);
		}

		TEST_METHOD(DotProduct)
		{
			Vector a(1, 2, 3);
			Vector b(2, 3, 4);
			Assert::AreEqual(20.0f, Dot(a, b));
		}

		TEST_METHOD(CrossProduct)
		{
			Vector a(1, 2, 3);
			Vector b(2, 3, 4);
			Assert::AreEqual(Vector(-1, 2, -1), Cross(a, b));
			Assert::AreEqual(Vector(1, -2, 1), Cross(b, a));
		}
	};

	TEST_CLASS(PointTests)
	{
	public:
		TEST_METHOD(PointDefaultCtor)
		{
			Point p;
			Assert::AreEqual(0.0f, p.x);
			Assert::AreEqual(0.0f, p.y);
			Assert::AreEqual(0.0f, p.z);
		}

		TEST_METHOD(PointCtor)
		{
			Point p(4.3f, -4.2f, 3.1f);
			Assert::AreEqual(4.3f, p.x);
			Assert::AreEqual(-4.2f, p.y);
			Assert::AreEqual(3.1f, p.z);
		}

		TEST_METHOD(AddVectorToPoint)
		{
			Point p(3.0f, -2.0f, 5.0f);
			Vector v(-2.0f, 3.0f, 1.0f);
			Point expected(1.0f, 1.0f, 6.0f);
			Point actual = p + v;
			Assert::AreEqual(expected, actual);
		}
	
		TEST_METHOD(SubtractVectorFromPoint)
		{
			Point p(3.0f, 2.0f, 1.0f);
			Vector v(5.0f, 6.0f, 7.0f);
			Point expected(-2.0f, -4.0f, -6.0f);
			Point actual = p - v;
			Assert::AreEqual(expected, actual);
		}
	};

	TEST_CLASS(ColorTests)
	{
	public:
		TEST_METHOD(ColorCtor)
		{
			Color c(-0.5f, 0.4f, 1.7f);
			Assert::AreEqual(-0.5f, c.r);
			Assert::AreEqual(0.4f, c.g);
			Assert::AreEqual(1.7f, c.b);
		}

		TEST_METHOD(ColorAdd)
		{
			Color a(0.9f, 0.6f, 0.75f);
			Color b(0.7f, 0.1f, 0.25f);
			Color sum = a + b;
			Assert::AreEqual(Color(1.6f, 0.7f, 1.0f), sum);
		}
		
		TEST_METHOD(ColorSubtract)
		{
			Color a(0.9f, 0.6f, 0.75f);
			Color b(0.7f, 0.1f, 0.25f);
			Color diff = a - b;
			Assert::AreEqual(Color(0.2f, 0.5f, 0.5f), diff);
		}
		
		TEST_METHOD(MultiplyScalar)
		{
			Color a(0.2f, 0.3f, 0.4f);
			Color scaled = a * 2.0f;
			Assert::AreEqual(Color(0.4f, 0.6f, 0.8f), scaled);
		}
		
		TEST_METHOD(ColorMultiply)
		{
			Color a(1.0f, 0.2f, 0.4f);
			Color b(0.9f, 1.0f, 0.1f);
			Color product = a * b;
			Assert::AreEqual(Color(0.9f, 0.2f, 0.04f), product);
		}
	};

	TEST_CLASS(CanvasTests)
	{
		TEST_METHOD(Ctor)
		{
			Canvas canvas(10, 20);
			Assert::AreEqual(10, canvas.width);
			Assert::AreEqual(20, canvas.height);
			Color black(0.0f, 0.0f, 0.0f);
			for (const auto& pixel : canvas.GetPixels())
			{
				Assert::AreEqual(black, pixel);
			}
		}

		TEST_METHOD(WritePixel)
		{
			Canvas canvas(10, 20);
			Color red(1.0f, 0.0f, 0.0f);
			canvas.PutPixel(2, 3, red);
			Assert::AreEqual(red, canvas.GetPixel(2, 3));
		}
	};
}
