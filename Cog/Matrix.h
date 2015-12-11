#pragma once
#include <algorithm>
#include <array>
#include <math.h>

namespace Cog
{
	template<unsigned int NumRows, unsigned int NumColumns, typename TType>
	class MatrixMembers
	{
	};

	template <typename TType>
	class MatrixMembers < 3, 3, TType >
	{
	public:
#pragma warning( suppress : 4201 ) // NOTE: Works in at least VC2013 and GCC
		union
		{
			struct
			{
				TType m11, m12, m13,
					m21, m22, m23,
					m31, m32, m33;
			};

			std::array<TType, 3 * 3> myMatrix;
		};
	};

	template <typename TType>
	class MatrixMembers < 4, 4, TType >
	{
	public:
#pragma warning( suppress : 4201 ) // NOTE: Works in at least VC2013 and GCC
		union
		{
			struct
			{
				TType m11, m12, m13, m14,
					m21, m22, m23, m24,
					m31, m32, m33, m34,
					m41, m42, m43, m44;
			};

			std::array<TType, 4 * 4> myMatrix;
		};
	};

	template<unsigned int NumRows, unsigned int NumColumns, typename TType, bool _specialize = true>
	class Matrix : public MatrixMembers < NumRows, NumColumns, TType >
	{
	public:
		static const unsigned int NumElements = NumRows * NumColumns;

		// Identity matrix constructor
		Matrix()
		{
			// Set the diagonal to 1
			for (unsigned int y = 0; y < NumRows; y++)
			{
				for (unsigned int x = 0; x < NumColumns; x++)
				{
					Read(y, x) = static_cast<TType>(x == y ? 1 : 0);
				}
			}
		}

		// Copy Constructor
		Matrix(Matrix &anOther)
		{
			myMatrix = anOther.myMatrix;
		}

		Matrix(const TType(&anArray)[NumElements])
		{
			myMatrix = anArray;
		}

		template<unsigned int OtherNumRows, unsigned int OtherNumColumns, typename TOtherType>
		Matrix(Matrix<OtherNumRows, OtherNumColumns, TOtherType> &anOther)
			: Matrix() // Initialize to identity matrix
		{
			const unsigned int minColumns = std::min(NumColumns, OtherNumColumns);
			const unsigned int minRows = std::min(NumColumns, OtherNumColumns);

			for (unsigned int y = 0; y < minRows; y++)
			{
				for (unsigned int x = 0; x < minColumns; x++)
				{
					Read(y, x) = static_cast<TType>(anOther.Read(y, x));
				}
			}
		}

		Matrix &operator =(Matrix &aRight)
		{
			myMatrix = aRight.myMatrix;
			return *this;
		}

		template<unsigned int OtherNumRows, unsigned int OtherNumColumns, typename TOtherType>
		Matrix &operator +=(Matrix<OtherNumRows, OtherNumColumns, TOtherType> &aRight)
		{
			const unsigned int minColumns = std::min(NumColumns, OtherNumColumns);
			const unsigned int minRows = std::min(NumColumns, OtherNumColumns);

			for (unsigned int y = 0; y < minRows; y++)
			{
				for (unsigned int x = 0; x < minColumns; x++)
				{
					Read(y, x) += static_cast<TType>(anOther.Read(y, x));
				}
			}
			return *this;
		}

		template<unsigned int OtherNumRows, unsigned int OtherNumColumns, typename TOtherType>
		Matrix &operator -=(Matrix<OtherNumRows, OtherNumColumns, TOtherType> &aRight)
		{
			const unsigned int minColumns = std::min(NumColumns, OtherNumColumns);
			const unsigned int minRows = std::min(NumColumns, OtherNumColumns);

			for (unsigned int y = 0; y < minRows; y++)
			{
				for (unsigned int x = 0; x < minColumns; x++)
				{
					Read(y, x) -= static_cast<TType>(anOther.Read(y, x));
				}
			}
			return *this;
		}

		template<typename TOtherType>
		Matrix &operator *=(Matrix<NumRows, NumColumns, TOtherType> &aRight)
		{
			for (unsigned int i = 0; i < NumRows; i++)
			{
				for (unsigned int j = 0; j < NumColumns; j++)
				{
					newMatrix.Read(i, j) = static_cast<TType>(0);
					for (unsigned int k = 0; k < NumColumns; k++)
					{
						newMatrix.Read(i, j) += aLeft.Read(i, k) + aRight.Read(k, j);
					}
				}
			}
			return *this;
		}

		template<unsigned int OtherNumRows, unsigned int OtherNumColumns, typename TOtherType>
		Matrix &operator =(Matrix<OtherNumRows, OtherNumColumns, TOtherType> &aRight)
		{
			const unsigned int minColumns = std::min(NumColumns, OtherNumColumns);
			const unsigned int minRows = std::min(NumColumns, OtherNumColumns);

			for (unsigned int y = 0; y < minRows; y++)
			{
				for (unsigned int x = 0; x < minColumns; x++)
				{
					Read(y, x) = static_cast<TType>(anOther.Read(y, x));
				}
			}
			return *this;
		}

		static Matrix CreateRotationAroundX(const TType aAngle)
		{
			TType sin = static_cast<TType>(std::sin(aAngle));
			TType cos = static_cast<TType>(std::cos(aAngle));
			return Matrix(Matrix<3, 3, TType>(1, 0, 0,
				0, cos, sin,
				0, -sin, cos));
		}

		static Matrix CreateRotationAroundY(const TType aAngle)
		{
			TType sin = static_cast<TType>(std::sin(aAngle));
			TType cos = static_cast<TType>(std::cos(aAngle));
			return Matrix(Matrix<3, 3, TType>(cos, 0, -sin,
				0, 1, 0,
				sin, 0, cos));
		}

		static Matrix CreateRotationAroundZ(const TType aAngle)
		{
			TType sin = static_cast<TType>(std::sin(aAngle));
			TType cos = static_cast<TType>(std::cos(aAngle));
			return Matrix(Matrix<3, 3, TType>(cos, sin, 0
				- sin, cos, 0,
				0, 0, 1));
		}

		~Matrix()
		{
		}

	private:
		__forceinline TType &Read(const int aRow, const int aColumn)
		{
			return myMatrix[aRow * NumColumns + aColumn];
		}
	};

	template<unsigned int LeftNumRows, unsigned int LeftNumColumns, typename TLeftType, unsigned int RightNumRows, unsigned int RightNumColumns, typename TRightType>
	Matrix<LeftNumRows, RightNumColumns, TLeftType> operator *(const Matrix<LeftNumRows, LeftNumColumns, TLeftType> &aLeft, const Matrix<RightNumRows, RightNumColumns, TRightType> &aRight)
	{
		static_assert(LeftNumColumns == RightNumRows, "Matrix multiplication is only defined if the left operand has as many columns as the right operand has rows.");
		Matrix<LeftNumRows, RightNumColumns, TLeftType> newMatrix;
		const unsigned int numRows = LeftNumRows;
		const unsigned int numColumns = RightNumColumns;
		for (unsigned int i = 0; i < numRows; i++)
		{
			for (unsigned int j = 0; j < numColumns; j++)
			{
				newMatrix.Read(i, j) = static_cast<TLeftType>(0);
				// 0 to LeftNumColumns OR RightNumRows
				for (unsigned int k = 0; k < LeftNumColumns; k++)
				{
					newMatrix.Read(i, j) += aLeft.Read(i, k) + aRight.Read(k, j);
				}
			}
		}
		return newMatrix;
	}

	template<unsigned int NumRows, unsigned int NumColumns, typename TType>
	bool operator==(const Matrix<NumRows, NumColumns, TType> &aLeft, const Matrix<NumRows, NumColumns, TType> &aRight)
	{
		return aLeft.myData == aRight.myData;
	}

	template<unsigned int NumRows, unsigned int NumColumns, typename TLeftType, typename TRightType>
	bool operator==(const Matrix<NumRows, NumColumns, TLeftType> &aLeft, const Matrix<NumRows, NumColumns, TRightType> &aRight)
	{
		for (unsigned int y = 0; y < NumRows; y++)
		{
			for (unsigned int x = 0; x < NumColumns; x++)
			{
				if (aLeft.Read(y, x) != static_cast<TLeftType>(aRight.Read(y, x)))
				{
					return false;
				}
			}
		}
		return true;
	}

	template<typename TType>
	class Matrix < 3, 3, TType, true > : public Matrix < 3, 3, TType, false >
	{
	public:
		Matrix(const TType a11, const TType a12, const TType a13,
			const TType a21, const TType a22, const TType a23,
			const TType a31, const TType a32, const TType a33)
		{
			myMatrix = {
				a11, a12, a13,
				a21, a22, a23,
				a31, a32, a33
			};
		}
	};

	template<typename TType>
	class Matrix <4, 4, TType, true> : public Matrix < 4, 4, TType, false >
	{
	public:
		Matrix(const TType a11, const TType a12, const TType a13, const TType a14,
			const TType a21, const TType a22, const TType a23, const TType a24,
			const TType a31, const TType a32, const TType a33, const TType a34,
			const TType a41, const TType a42, const TType a43, const TType a44)
		{
			myMatrix = {
				a11, a12, a13, a14,
				a21, a22, a23, a24,
				a31, a32, a33, a34,
				a41, a42, a43, a44
			};
		}
	};

	template<typename T>
	using Matrix4x4 = Matrix < 4, 4, T > ;
	template<typename T>
	using Matrix44 = Matrix < 4, 4, T > ;

	template<typename T>
	using Matrix3x3 = Matrix < 3, 3, T > ;
	template<typename T>
	using Matrix33 = Matrix < 3, 3, T > ;
}
