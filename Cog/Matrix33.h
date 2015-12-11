#pragma once
#include "vector3.h"
#include <algorithm>
#include <array>
#include <math.h>

namespace Cog
{
	// Forward declarations
	//
	template<typename TYPE>
	class Matrix44;

	template<typename TYPE>
	class Matrix33
	{
	public:     // Constants to avoid using magic numbers
		//
		static const unsigned int   NumRows = 3,
			NumColumns = 3,
			NumElements = NumRows * NumColumns;

		// Initializes the matrix to the identity matrix
		//
		Matrix33()
		{
			// Set the diagonal to 1
			for (unsigned int y = 0; y < NumRows; y++)
			{
				for (unsigned int x = 0; x < NumColumns; x++)
				{
					Read(y, x) = static_cast<TYPE>(x == y ? 1 : 0);
				}
			}
		}

		// Initializes the matrix with the data from anOther
		//
		Matrix33(const Matrix33 &anOther)
		{
			myMatrix = anOther.myMatrix;
		}

		// Initializes the matrix with the 3x3-part from anOther
		//
		Matrix33(const Matrix44<TYPE> &anOther);

		// Initializes the matrix with the static_cast'ed data from anOther which uses another base type
		//
		template<typename U>
		Matrix33(const Matrix33<U> &anOther)
		{
			for (unsigned int y = 0; y < NumRows; y++)
			{
				for (unsigned int x = 0; x < NumColumns; x++)
				{
					Read(y, x) = static_cast<U>(anOther.Read(y, x));
				}
			}
		}

		// Initializes the matrix with the data from an array
		//
		// Explanation:
		// This allows the syntax: Matrix33 identity({1, 0, 0, 0, 1, 0, 0, 0, 1});
		//
		Matrix33(const TYPE(&anArray)[NumElements])
		{
			for (int i = 0; i < NumElements; i++)
			{
				myMatrix[i] = anArray[i];
			}
		}

		// Initializes the matrix with plain values
		//
		Matrix33(
			const TYPE a11, const TYPE a12, const TYPE a13,
			const TYPE a21, const TYPE a22, const TYPE a23,
			const TYPE a31, const TYPE a32, const TYPE a33)
		{
			myMatrix[0] = a11;
			myMatrix[1] = a12;
			myMatrix[2] = a13;

			myMatrix[3] = a21;
			myMatrix[4] = a22;
			myMatrix[5] = a23;

			myMatrix[6] = a31;
			myMatrix[7] = a32;
			myMatrix[8] = a33;
		}

		// Adds and assigns the values of aRight to this matrix
		//
		Matrix33 &operator +=(const Matrix33 &aRight)
		{
			for (int i = 0; i < NumElements; i++)
			{
				myMatrix[i] += aRight.myMatrix[i];
			}
			return *this;
		}

		// Subtract and assigns the values of aRight to this matrix
		//
		Matrix33 &operator -=(const Matrix33 &aRight)
		{
			for (int i = 0; i < NumElements; i++)
			{
				myMatrix[i] -= aRight.myMatrix[i];
			}
			return *this;
		}

		// Multiplies this matrix with aRight
		//
		Matrix33 &operator *=(const Matrix33 &aRight)
		{
			*this = *this * aRight;
			return *this;
		}

		// Sets the values of this matrix to those of aRight
		//
		Matrix33 &operator =(const Matrix33 &aRight)
		{
			myMatrix = aRight.myMatrix;
			return *this;
		}

		// Transposes the matrix and returns *this
		//
		Matrix33 &Transpose()
		{
			Matrix33 copy = *this;
			for (int y = 0; y < NumRows; y++)
			{
				for (int x = 0; x < NumColumns; x++)
				{
					Read(y, x) = copy.Read(x, y);
				}
			}
			return *this;
		}

		static Matrix33 CreateTranslation(const TYPE aX, const TYPE aY)
		{
			return Matrix33(
				1, 0, aX,
				0, 1, aY,
				0, 0, 1);
		}

		static Matrix33 CreateScale(const TYPE aX, const TYPE aY)
		{
			return Matrix33(
				aX, 0, 0,
				0, aY, 0,
				0, 0, 1);
		}

		// Creates a transformation matrix for rotating anAngle rad around the x-axis
		//
		static Matrix33 CreateRotateAroundX(const TYPE anAngle)
		{
			TYPE sin = static_cast<TYPE>(std::sin(anAngle));
			TYPE cos = static_cast<TYPE>(std::cos(anAngle));
			return Matrix33(1, 0, 0,
				0, cos, sin,
				0, -sin, cos);
		}

		// Creates a transformation matrix for rotating anAngle rad around the y-axis
		//
		static Matrix33 CreateRotateAroundY(const TYPE anAngle)
		{
			TYPE sin = static_cast<TYPE>(std::sin(anAngle));
			TYPE cos = static_cast<TYPE>(std::cos(anAngle));
			return Matrix33(cos, 0, -sin,
				0, 1, 0,
				sin, 0, cos);
		}

		// Creates a transformation matrix for rotating anAngle rad around the z-axis
		//
		static Matrix33 CreateRotateAroundZ(const TYPE anAngle)
		{
			TYPE sin = static_cast<TYPE>(std::sin(anAngle));
			TYPE cos = static_cast<TYPE>(std::cos(anAngle));
			return Matrix33(cos, sin, 0,
				-sin, cos, 0,
				0, 0, 1);
		}

		// Returns a transposed copy of aMatrix
		//
		static Matrix33 Transpose(Matrix33 aMatrix)
		{
			return aMatrix.Transpose();
		}

		// The data of this matrix
		//
#pragma warning( suppress : 4201 ) // NOTE: This works fine in VC2013 and GCC so I'm keeping it. //MAHAM
		union
		{
			struct
			{
				TYPE    m11, m12, m13,
					m21, m22, m23,
					m31, m32, m33;
			};

			std::array<TYPE, NumElements> myMatrix;
		};

		// Pre-created matrices
		//
		static const Matrix33   Identity,   // Identity matrix
			Zero;       // Matrix with all 0

		__forceinline TYPE &Read(const int aRow, const int aColumn)
		{
			return myMatrix[aRow * NumColumns + aColumn];
		}

		__forceinline TYPE Read(const int aRow, const int aColumn) const
		{
			return myMatrix[aRow * NumColumns + aColumn];
		}
	};

	template <typename TYPE>
	const Matrix33<TYPE> Matrix33<TYPE>::Zero(0, 0, 0, 0, 0, 0, 0, 0, 0);
	template <typename TYPE>
	const Matrix33<TYPE> Matrix33<TYPE>::Identity;
}
#include "Matrix44.h"
namespace Cog
{
	template <typename TYPE>
	Matrix33<TYPE>::Matrix33(const Matrix44<TYPE> &anOther)
	{
		for (unsigned int y = 0; y < 3; y++)
		{
			for (unsigned int x = 0; x < 3; x++)
			{
				Read(y, x) = static_cast<TYPE>(anOther.Read(y, x));
			}
		}
	}

	// Alias for Matrix33<float>. Add more if needed.
	//
	using Matrix33f = Matrix33 < float > ;
	
	// Returns a new matrix which is the sum of aLeft and aRight
	//
	template<typename TYPE>
	Matrix33<TYPE> operator +(Matrix33<TYPE> aLeft, const Matrix33<TYPE> &aRight)
	{
		return aLeft += aRight;
	}
	
	// Returns a new matrix wich is the difference of aLeft and aRight
	//
	template<typename TYPE>
	Matrix33<TYPE> operator -(Matrix33<TYPE> aLeft, const Matrix33<TYPE> &aRight)
	{
		return aLeft -= aRight;
	}
	
	// Returns a new matrix which is the product of aLeft and aRight
	//
	template<typename TYPE>
	Matrix33<TYPE> operator *(const Matrix33<TYPE> &aLeft, const Matrix33<TYPE> &aRight)
	{
		Matrix33<TYPE> newMatrix;
		const unsigned int numRows = 3;
		const unsigned int numColumns = 3;
		for (unsigned int i = 0; i < numRows; i++)
		{
			for (unsigned int j = 0; j < numColumns; j++)
			{
				newMatrix.Read(i, j) = static_cast<TYPE>(0);
				for (unsigned int k = 0; k < 3; k++)
				{
					newMatrix.Read(i, j) += aLeft.Read(i, k) * aRight.Read(k, j);
				}
			}
		}
		return newMatrix;
	}
	
	// Returns a new matrix which is the product of the vector aLeft and the matrix aRight
	//
	template<typename TYPE>
	Vector3<TYPE> operator *(Vector3<TYPE> &aLeft, const Matrix33<TYPE> &aRight)
	{
		Vector3<TYPE> out;
		out.x = (aRight.m11 * aLeft.x) + (aRight.m12 * aLeft.y) + (aRight.m13 * aLeft.z);
		out.y = (aRight.m21 * aLeft.x) + (aRight.m22 * aLeft.y) + (aRight.m23 * aLeft.z);
		out.z = (aRight.m31 * aLeft.x) + (aRight.m32 * aLeft.y) + (aRight.m33 * aLeft.z);
		return out;
	}

	// Compares aLeft and aRight componentwise
	//
	template<typename TYPE>
	bool operator ==(const Matrix33<TYPE> &aLeft, const Matrix33<TYPE> &aRight)
	{
		return aLeft.myMatrix == aRight.myMatrix;
	}

	// Returns the negated result of aLeft == aRight
	//
	template<typename TYPE>
	bool operator !=(const Matrix33<TYPE> &aLeft, const Matrix33<TYPE> &aRight)
	{
		return (aLeft == aRight) == false;
	}
}
