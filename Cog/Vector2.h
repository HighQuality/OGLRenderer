#pragma once
#include <cmath>

namespace Cog
{
	template<typename TYPE>
	class Vector2
	{
	public:
		Vector2(void)
		{
			x = static_cast<TYPE>(0);
			y = static_cast<TYPE>(0);
		}
		Vector2(const Vector2 &aVector2)
		{
			x = aVector2.x;
			y = aVector2.y;
		}
		template<typename U> explicit Vector2(const Vector2<U> &aVector2)
		{
			x = static_cast<TYPE>(aVector2.x);
			y = static_cast<TYPE>(aVector2.y);
		}
		Vector2(const TYPE anX, const TYPE aY)
		{
			x = anX;
			y = aY;
		}

		friend Vector2 operator +(Vector2 aLeft, const Vector2 &aRight)
		{
			return aLeft += aRight;
		}

		friend Vector2 operator -(Vector2 aLeft, const Vector2 &aRight)
		{
			return aLeft -= aRight;
		}

		friend Vector2 operator *(Vector2 aLeft, const TYPE aRight)
		{
			return aLeft *= aRight;
		}

		friend Vector2 operator *(const TYPE aRight, Vector2 aLeft)
		{
			return aLeft *= aRight;
		}

		friend Vector2 operator /(Vector2 aLeft, const TYPE aRight)
		{
			return aLeft /= aRight;
		}

		friend Vector2 operator /(const TYPE aRight, Vector2 aLeft)
		{
			return aLeft /= aRight;
		}

		friend Vector2 operator -(Vector2 aRight)
		{
			return aRight * static_cast<TYPE>(-1);
		}

		friend bool operator ==(const Vector2 &aLeft, const Vector2 &aRight)
		{
			return aLeft.x == aRight.x &&
				aLeft.y == aRight.y;
		}

		friend bool operator !=(const Vector2 &aLeft, const Vector2 &aRight)
		{
			return (aLeft == aRight) == false;
		}

		Vector2 &operator =(const Vector2 &aRight)
		{
			x = aRight.x;
			y = aRight.y;
			return *this;
		}

		Vector2 &operator +=(const Vector2 &aRight)
		{
			x += aRight.x;
			y += aRight.y;
			return *this;
		}
		Vector2 &operator -=(const Vector2 &aRight)
		{
			x -= aRight.x;
			y -= aRight.y;
			return *this;
		}
		Vector2 &operator *=(const TYPE aRight)
		{
			x *= aRight;
			y *= aRight;
			return *this;
		}
		Vector2 &operator /=(const TYPE aRight)
		{
			x /= aRight;
			y /= aRight;
			return *this;
		}

		TYPE Length(void) const
		{
			return static_cast<TYPE>(sqrt(x * x + y * y));
		}
		TYPE Length2(void) const
		{
			TYPE length = Length();
			return length * length;
		}
		TYPE Dot(const Vector2<TYPE> &aRight) const
		{
			return x * aRight.x + y * aRight.y;
		}
		Vector2 GetNormalized(void) const
		{
			return *this / Length();
		}

		Vector2 &Normalize(void)
		{
			*this = GetNormalized();
			return *this;
		}

		TYPE x,
			y;

		static TYPE Dot(const Vector2 &aFirstVector, const Vector2 &aSecondVector)
		{
			return aFirstVector.Dot(aSecondVector);
		}
		static Vector2 Normalize(Vector2 aVector)
		{
			return aVector.GetNormalized();
		}

		static const Vector2 Zero,
			UnitX,
			UnitY,
			One;
	};

	using Vector2c = Vector2 < char > ;
	using Vector2i = Vector2 < int > ;
	using Vector2ui = Vector2 < unsigned int > ;
	using Vector2f = Vector2 < float > ;
	using Vector2d = Vector2 < double > ;

	template<typename TYPE> const Vector2<TYPE> Vector2<TYPE>::Zero(0, 0);
	template<typename TYPE> const Vector2<TYPE> Vector2<TYPE>::UnitX(1, 0);
	template<typename TYPE> const Vector2<TYPE> Vector2<TYPE>::UnitY(0, 1);
	template<typename TYPE> const Vector2<TYPE> Vector2<TYPE>::One(1, 1);
}
