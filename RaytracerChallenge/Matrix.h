#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

#include "Math.h"
#include "Vector.h"
#include "Point.h"

//N*N matrix
template<std::size_t N>
class Matrix
{
public:
	Matrix()
		:mat(N* N, 0.0f) {}
	float& operator()(int row, int column)
	{
		return mat[row * N + column];
	}
	const float& operator()(int row, int column) const
	{
		return mat[row * N + column];
	}
	bool operator==(const Matrix& rhs)
	{
		return std::equal(mat.begin(), mat.end(), rhs.mat.begin(), Equals);
	}
	bool operator!=(const Matrix& rhs)
	{
		return !(*this == rhs);
	}
	Matrix GetTransposed() const
	{
		Matrix transposed;
		for (std::size_t i = 0; i < transposed.mat.size(); ++i)
		{
			transposed.mat[i] = operator()(i % N, i / N);
		}
		return transposed;
	}
	Matrix<N - 1> Submatrix(int row, int column) const
	{
		Matrix<N - 1> submatrix;
		int index = -1;
		std::copy_if(mat.begin(), mat.end(), submatrix.mat.begin(),
			[&index, row, column](float entry)
			{
				++index;
				return (index / N) != row && (index % N) != column;
			});
		return submatrix;
	}
	float Minor(int row, int column) const
	{
		return Submatrix(row, column).Determinant();
	}
	float Cofactor(int row, int column) const
	{
		auto minor = Minor(row, column);
		return (row + column) % 2 == 0 ? minor : -minor;
	}
	float Determinant() const
	{
		float determinant = 0.0f;
		for (std::size_t i = 0; i < N; ++i)
		{
			determinant += operator()(0, i) * Cofactor(0, i);
		}
		return determinant;
	}
	std::pair<bool, Matrix> Inverse()
	{
		float determinant = Determinant();
		if (Equals(determinant, 0.0f))
		{
			return { false, {} };
		}
		Matrix cofactors;
		for (std::size_t i = 0; i < N; ++i)
		{
			for (std::size_t j = 0; j < N; ++j)
			{
				cofactors(i, j) = Cofactor(i, j);
			}
		}
		Matrix tranposed = cofactors.GetTransposed();
		std::for_each(tranposed.mat.begin(), tranposed.mat.end(),
			[determinant](float& entry)
			{
				entry /= determinant;
			});
		return { true, tranposed };
	}
private:
	std::vector<float> mat;

	// necessary for Submatrix function
	template<std::size_t U>
	friend class Matrix;
};

typedef Matrix<2> Mat2;
typedef Matrix<3> Mat3;
typedef Matrix<4> Mat4;

template<> float Matrix<2>::Determinant() const
{
	return mat[0] * mat[3] - mat[1] * mat[2];
}


static float Dot(const Mat4& lhs, int row, const Mat4& rhs, int column)
{
	float dot = 0.0f;
	for (std::size_t i = 0; i < 4; i++)
	{
		dot += lhs(row, i) * rhs(i, column);
	}
	return dot;
}

static float Dot(const Mat4& lhs, int row, const Vector& rhs)
{
	return lhs(row, 0) * rhs.x +
		   lhs(row, 1) * rhs.y +
		   lhs(row, 2) * rhs.z;
}

static float Dot(const Mat4& lhs, int row, const Point& rhs)
{
	return lhs(row, 0) * rhs.x +
		   lhs(row, 1) * rhs.y +
		   lhs(row, 2) * rhs.z +
		   lhs(row, 3); // translation 
}

inline Mat4 operator*(const Mat4& lhs, const Mat4& rhs)
{
	Mat4 product;
	for (std::size_t i = 0; i < 4; i++)
	{
		for (std::size_t j = 0; j < 4; j++)
		{
			product(j, i) = Dot(rhs, j, lhs, i);
		}
	}
	return product;
}

inline Vector operator*(const Mat4& lhs, const Vector& rhs)
{
	Vector product;
	product.x = Dot(lhs, 0, rhs);
	product.y = Dot(lhs, 1, rhs);
	product.z = Dot(lhs, 2, rhs);
	return product;
}

inline Point operator*(const Mat4& lhs, const Point& rhs)
{
	Point product;
	product.x = Dot(lhs, 0, rhs);
	product.y = Dot(lhs, 1, rhs);
	product.z = Dot(lhs, 2, rhs);
	return product;
}

//inline float Determinant(const Mat2& mat)
//{
//	return mat(0, 0) * mat(1, 1) - mat(0, 1) * mat(1, 0);
//}
//
//inline float Determinant(const Mat3& mat);
//inline float Determinant(const Mat4& mat);
//
//inline float Minor(const Mat3& mat, int row, int column) 
//{
//	return Determinant(mat.Submatrix(row, column));
//}
//
//inline float Minor(const Mat4& mat, int row, int column)
//{
//	return Determinant(mat.Submatrix(row, column));
//}
//
//inline float Cofactor(const Mat3& mat, int row, int column)
//{
//	auto minor = Minor(mat, row, column);
//	return (row + column) % 2 == 0 ? minor : -minor;
//}
//
//inline float Cofactor(const Mat4& mat, int row, int column)
//{
//	auto minor = Minor(mat, row, column);
//	return (row + column) % 2 == 0 ? minor : -minor;
//}
//
//float Determinant(const Mat3& mat) 
//{
//	float determinant = 0.0f;
//	for (std::size_t i = 0; i < 3; ++i)
//	{
//		determinant += mat(0, i) * Cofactor(mat, 0, i);
//	}
//	return determinant;
//}
//
//float Determinant(const Mat4& mat)
//{
//	float determinant = 0.0f;
//	for (std::size_t i = 0; i < 4; ++i)
//	{
//		determinant += mat(0, i) * Cofactor(mat, 0, i);
//	}
//	return determinant;
//}