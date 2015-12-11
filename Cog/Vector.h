#pragma once
#include <cmath>
#include "Matrix.h"

namespace Cog
{
	template <typename TType>
	class MatrixMembers < 1, 2, TType >
	{
	public:
#pragma warning( suppress : 4201 ) // NOTE: Works in at least VC2013 and GCC
		union
		{
			struct
			{
				TType x, y;
			};

			std::array<TType, 2> myMatrix;
		};
	};
	template <typename TType>
	class MatrixMembers < 1, 3, TType >
	{
	public:
#pragma warning( suppress : 4201 ) // NOTE: Works in at least VC2013 and GCC
		union
		{
			struct
			{
				TType x, y, z;
			};

			std::array<TType, 3> myMatrix;
		};
	};
	template <typename TType>
	class MatrixMembers < 1, 4, TType >
	{
	public:
#pragma warning( suppress : 4201 ) // NOTE: Works in at least VC2013 and GCC
		union
		{
			struct
			{
				TType x, y, z, w;
			};

			std::array<TType, 4> myMatrix;
		};
	};

	template <typename T, int numDimensions, bool _specialize = true>
	class Vector : public Matrix<1, numDimensions, T>
	{
	public:
		Vector()
		{
			Zero();
		}

		__forceinline Vector operator+ (const Vector &vector) const
		{
			Vector result = *this;
			for (int i = 0; i < numDimensions; i++)
				result[i] += vector[i];
			return result;
		}
		__forceinline Vector operator- (const Vector &vector) const
		{
			return *this + (-vector);
		}
		__forceinline Vector operator *(T scalar) const
		{
			Vector result = *this;
			for (int i = 0; i < numDimensions; i++)
				result[i] *= scalar;
			return result;
		}
		__forceinline Vector operator /(T scalar) const
		{
			return *this * (static_cast<T>(1) / scalar);
		}
		__forceinline bool operator==(const Vector &vector) const
		{
			for (int i = 0; i < numDimensions; i++)
				if ((*this)[i] != vector[i])
					return false;
			return true;
		}
		__forceinline bool operator !=(const Vector &vector) const
		{
			return (*this == vector) == false;
		}
		__forceinline Vector &operator=(const Vector &vector)
		{
			for (int i = 0; i < numDimensions; i++)
				(*this)[i] = vector[i];
			return *this;
		}
		__forceinline Vector &operator+= (const Vector &vector)
		{
			*this = *this + vector;
			return *this;
		}
		__forceinline Vector &operator-= (const Vector &vector)
		{
			*this = *this - vector;
			return *this;
		}
		__forceinline Vector &operator*= (T scalar)
		{
			*this = *this * scalar;
			return *this;
		}
		__forceinline Vector &operator/= (T scalar)
		{
			*this = *this / scalar;
			return *this;
		}
		__forceinline T Dot(Vector right) const
		{
			T sum = static_cast<T>(0);
			for (int i = 0; i < numDimensions; i++)
				sum += (*this)[i] * right[i];
			return sum;
		}
		__forceinline T Length() const
		{
			return static_cast<T>(sqrt(Dot(*this)));
		}
		__forceinline T Length2() const
		{
			return Dot(*this);
		}
		__forceinline Vector Normalized() const
		{
			return (*this) / Length();
		}
		__forceinline void Normalize()
		{
			*this = Normalized();
		}
	protected:
		__forceinline void Zero()
		{
			for (int i = 0; i < numDimensions; i++)
				(*this)[i] = static_cast<T>(0);
		}
		template <typename U, int dimensions>
		void Copy(const Vector<U, dimensions> &vector)
		{
			static int minDim = dim < numDimensions ? dim : numDimensions;
			Zero();
			for (int i = 0; i < minDim; i++)
				(*this)[i] = static_cast<T>(vector[i]);
		}

		__forceinline T &operator[](int index)
		{
			return myMatrix[index];
		}
		__forceinline T operator[](int index) const
		{
			return *myMatrix[index];
		}
	};
	
	template <typename T>
	class Vector<T, 2, true> : public Vector < T, 2, false >
	{
	public:
		__forceinline Vector()
		{
		}
		__forceinline Vector(T x, T y)
		{
			(*this)[0] = x;
			(*this)[1] = y;
		}
		template <typename U, int dim, bool spec>
		explicit Vector(const Vector<U, dim, spec> &vector)
		{
			Copy(vector);
		}
	};

	template <typename T>
	class Vector<T, 3, true> : public Vector < T, 3, false >
	{
	public:
		__forceinline Vector()
		{
		}
		__forceinline Vector(T x, T y, T z)
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[3] = z;
		}
		template <typename U, int dim, bool spec>
		explicit Vector(const Vector<U, dim, spec> &vector)
		{
			Copy(vector);
		}
		__forceinline Vector Cross(const Vector &aOtherVector) const
		{
			return Vector(
				(*this)[1] * aOtherVector[2] - (*this)[2] * aOtherVector[1],
				(*this)[2] * aOtherVector[0] - (*this)[0] * aOtherVector[2],
				(*this)[0] * aOtherVector[1] - (*this)[1] * aOtherVector[0]);
		}
	};

	template <typename T>
	class Vector<T, 4, true> : public Vector <T, 4, false>
	{
	public:
		__forceinline Vector()
		{
		}
		__forceinline Vector(T x, T y, T z, T w)
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
			(*this)[3] = w;
		}
		template <typename U, int dim, bool spec>
		explicit Vector(const Vector<U, dim, spec> &vector)
		{
			Copy(vector);
		}
	};

	template<typename T>
	using Vector2 = Vector<T, 2>;
	template<typename T>
	using Vector3 = Vector<T, 3>;
	template<typename T>
	using Vector4 = Vector<T, 4>;

	using Vector2c = Vector2 < char >;
	using Vector2i = Vector2 < int >;
	using Vector2ui = Vector2 < unsigned int >;
	using Vector2f = Vector2 < float >;
	using Vector2d = Vector2 < double >;
	using Point2c = Vector2 < char >;
	using Point2i = Vector2 < int >;
	using Point2ui = Vector2 < unsigned int >;
	using Point2f = Vector2 < float >;
	using Point2d = Vector2 < double >;
	using Vector3c = Vector3 < char >;
	using Vector3i = Vector3 < int >;
	using Vector3ui = Vector3 < unsigned int >;
	using Vector3f = Vector3 < float >;
	using Vector3d = Vector3 < double >;
	using Point3c = Vector3 < char >;
	using Point3i = Vector3 < int >;
	using Point3ui = Vector3 < unsigned int >;
	using Point3f = Vector3 < float >;
	using Point3d = Vector3 < double >;
	using Vector4c = Vector4 < char >;
	using Vector4i = Vector4 < int >;
	using Vector4ui = Vector4 < unsigned int >;
	using Vector4f = Vector4 < float >;
	using Vector4d = Vector4 < double >;
	using Point4c = Vector4 < char >;
	using Point4i = Vector4 < int >;
	using Point4ui = Vector4 < unsigned int >;
	using Point4f = Vector4 < float >;
	using Point4d = Vector4 < double >;
}
