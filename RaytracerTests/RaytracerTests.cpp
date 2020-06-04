#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../RaytracerChallenge/Vector.h"
#include "../RaytracerChallenge/Point.h"
#include "../RaytracerChallenge/Color.h"
#include "../RaytracerChallenge/Canvas.h"
#include "../RaytracerChallenge/Matrix.h"

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

	TEST_CLASS(MatrixTests)
	{
		TEST_METHOD(DefaultCtor)
		{
			Mat4 m;
			for (std::size_t i = 0; i < m.dim(); ++i)
			{
				for (std::size_t j = 0; j < m.dim(); ++j)
				{
					Assert::AreEqual(0.0f, m(i, j));
				}
			}
		}

		TEST_METHOD(SetAndGet)
		{
			Mat4 m;
			m(0, 0) = 1.f;
			m(0, 1) = 2.f;
			m(0, 2) = 3.f;
			m(0, 3) = 4.f;

			m(1, 0) = 5.5f;
			m(1, 1) = 6.5f;
			m(1, 2) = 7.5f;
			m(1, 3) = 8.5f;

			m(2, 0) = 9.f;
			m(2, 1) = 10.f;
			m(2, 2) = 11.f;
			m(2, 3) = 12.f;

			m(3, 0) = 13.5f;
			m(3, 1) = 14.5f;
			m(3, 2) = 15.5f;
			m(3, 3) = 16.5f;

			Assert::AreEqual(1.0f, m(0, 0));
			Assert::AreEqual(4.0f, m(0, 3));
			Assert::AreEqual(5.5f, m(1, 0));
			Assert::AreEqual(7.5f, m(1, 2));
			Assert::AreEqual(11.0f, m(2, 2));
			Assert::AreEqual(13.5f, m(3, 0));
			Assert::AreEqual(15.5f, m(3, 2));
		}

		TEST_METHOD(Mat2Representable)
		{
			Mat2 m;
			m(0, 0) = -3.0f;
			m(0, 1) = 5.f;
			m(1, 0) = 1.f;
			m(1, 1) = -2.f;

			Assert::AreEqual(-3.0f, m(0, 0));
			Assert::AreEqual(5.0f, m(0, 1));
			Assert::AreEqual(1.0f, m(1, 0));
			Assert::AreEqual(-2.0f, m(1, 1));
		}

		TEST_METHOD(Equality)
		{
			Mat4 a;
			for (std::size_t i = 0; i < a.dim(); ++i)
			{
				for (auto j = 0u; j < a.dim(); ++j)
				{
					a(i, j) = i + j;
				}
			}
			Mat4 b = a;
			// Had to do this weird way to get by dumb errors from testing framework
			bool equal = a == b;
			Assert::AreEqual(true, equal);
		}

		TEST_METHOD(Equality2)
		{
			Mat4 a;
			Mat4 b;

			b(3, 3) = 1.0f;
			bool equal = a == b;
			Assert::AreEqual(false, equal);
		}

		TEST_METHOD(MatrixMultiplication)
		{
			Mat4 a{1.f, 2.f, 3.f, 4.f, 
				   5.f, 6.f, 7.f, 8.f, 
				   9.f, 8.f, 7.f, 6.f, 
				   5.f, 4.f, 3.f, 2.f };
			Mat4 b{ -2.f, 1.f, 2.f, 3.f,
				   3.f, 2.f, 1.f, -1.f,
				   4.f, 3.f, 6.f, 5.f,
				   1.f, 2.f, 7.f, 8.f };
			Mat4 product = a * b;
			Mat4 expected{ 20.f, 22.f, 50.f, 48.f,
						  44.f, 54.f, 114.f, 108.f,
						  40.f, 58.f, 110.f, 102.f,
						  16.f, 26.f, 46.f, 42.f };
			bool equal = expected == product;
			Assert::AreEqual(true, equal);
		}

		TEST_METHOD(MatrixVectorMultiplication)
		{
			Mat4 a{ 1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1 };
			Vector v(1, 2, 3);
			Vector product = a * v;
			Assert::AreEqual(Vector(14, 22, 32), product);
		}

		TEST_METHOD(MatrixPointMultiplication)
		{
			Mat4 a{ 1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1 };
			Point p(1, 2, 3);
			Point product = a * p;
			Assert::AreEqual(Point(18, 24, 33), product);
		}

		TEST_METHOD(IdentityMultiplication)
		{
			Mat4 a{ 0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32 };
			Mat4 identity = Mat4::Identity();
			Mat4 product = a * identity;
			Mat4 expected{ 0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32 };
			bool equal = a == expected;
			Assert::AreEqual(true, equal);
		}

		TEST_METHOD(Transpose)
		{
			Mat4 a{ 0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8};
			Mat4 transposed = a.GetTransposed();
			Mat4 expected{ 0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8 };
			bool equal = transposed == expected;
			Assert::AreEqual(true, equal);
		}

		TEST_METHOD(TransposeIdentity)
		{
			Mat4 identity = Mat4::Identity();
			Mat4 transposed = identity.GetTransposed();
			Mat4 expected = Mat4::Identity();
			bool equal = transposed == expected;
			Assert::AreEqual(true, equal);
		}

		TEST_METHOD(DeterminantMat2)
		{
			Mat2 m{ 1, 5, 
					-3, 2 };
			Assert::AreEqual(17.0f, m.Determinant());
		}

		TEST_METHOD(SubmatrixMat3)
		{
			Mat3 a{ 1, 5, 0,
					-3, 2, 7,
					0, 6, -3 };
			Mat2 sub = a.Submatrix(0, 2);
			Mat2 expected{
				-3, 2,
				 0, 6
			};
			bool equal = sub == expected;
			Assert::AreEqual(true, equal);
		}

		TEST_METHOD(SubmatrixMat4)
		{
			Mat4 a{ 1, 5, 0, 1,
					-3, 2, 7, 1,
					0, 6, -3, 1,
					0, 0, 0, 1};
			Mat3 sub = a.Submatrix(0, 0);
			Mat3 expected{
				2, 7, 1,
				6, -3, 1,
				0, 0, 1
			};
			bool equal = sub == expected;
			Assert::AreEqual(true, equal);
		}

		TEST_METHOD(Minor)
		{
			Mat3 m{
				3, 5, 0,
				2, -1, -7,
				6, -1, 5
			};
			
			Assert::AreEqual(25.0f, m.Minor(1, 0));
		}

		TEST_METHOD(Cofactor)
		{
			Mat3 m{
				3, 5, 0,
				2, -1, -7,
				6, -1, 5
			};

			Assert::AreEqual(-25.0f, m.Cofactor(1, 0));
		}

		TEST_METHOD(DeterminantMat3)
		{
			Mat3 m{
				1, 2, 6,
				-5, 8, -4,
				2, 6, 4
			};

			Assert::AreEqual(-196.0f, m.Determinant());
		}

		TEST_METHOD(DeterminantMat4)
		{
			Mat4 m
			{
				-2, -8, 3, 5,
				-3, 1, 7, 3,
				1, 2, -9, 6,
				-6, 7, 7, -9
			};

			Assert::AreEqual(-4071.f, m.Determinant());
		}
	};
}
