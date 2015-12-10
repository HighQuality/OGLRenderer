#include "Color.h"

namespace Cog
{
	const Color Color::White(255, 255, 255);
	const Color Color::CornflowerBlue(100, 149, 237);
	const Color Color::Red(255, 0, 0);
	const Color Color::Green(0, 255, 0);
	const Color Color::Blue(0, 0, 255);
	const Color Color::Gray(128, 128, 128);
	const Color Color::Black(0, 0, 0);
	const Color Color::Yellow(255, 255, 0);
	const Color Color::Purple(255, 0, 255);
	const Color Color::Cyan(0, 255, 255);

	Color::Color(void)
	{
		r = 0;
		g = 0;
		b = 0;
		a = 255;
	}

	Color::Color(const Color &anOther)
	{
		*this = anOther;
	}

	Color::Color(int red, int green, int blue, int alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	Color::Color(int red, int green, int blue)
		: Color(red, green, blue, 255)
	{
	}

	Vector4f Color::ToVector4()
	{
		return Vector4f(static_cast<float>(r) / 255.f, static_cast<float>(g) / 255.f, static_cast<float>(b) / 255.f, static_cast<float>(a) / 255.f);
	}

	Color operator +(Color aLeft, const Color &aRight)
	{
		return aLeft += aRight;
	}

	Color operator -(Color aLeft, const Color &aRight)
	{
		return aLeft -= aRight;
	}

	Color operator *(Color aLeft, const float aRight)
	{
		return aLeft *= aRight;
	}

	Color operator /(Color aLeft, const float aRight)
	{
		return aLeft /= aRight;
	}

	bool operator ==(const Color &aLeft, const Color &aRight)
	{
		return (aLeft.r == aRight.r && aLeft.g == aRight.g &&
			aLeft.b == aRight.b && aLeft.a == aRight.a);
	}

	bool operator !=(const Color &aLeft, const Color &aRight)
	{
		return (aLeft == aRight) == false;
	}

	Color &Color::operator =(const Color &aRight)
	{
		r = aRight.r;
		g = aRight.g;
		b = aRight.b;
		a = aRight.a;
		return *this;
	}

	Color &Color::operator +=(const Color &aRight)
	{
		r += aRight.r;
		g += aRight.g;
		b += aRight.b;
		a += aRight.a;
		return *this;
	}
	Color &Color::operator -=(const Color &aRight)
	{
		r -= aRight.r;
		g -= aRight.g;
		b -= aRight.b;
		a -= aRight.a;
		return *this;
	}
	Color &Color::operator *=(float aRight)
	{
		r = static_cast<int>(static_cast<float>(r)* aRight);
		g = static_cast<int>(static_cast<float>(g)* aRight);
		b = static_cast<int>(static_cast<float>(b)* aRight);
		a = static_cast<int>(static_cast<float>(a)* aRight);
		return *this;
	}
	Color &Color::operator /=(const float aRight)
	{
		r = static_cast<int>(static_cast<float>(r) / aRight);
		g = static_cast<int>(static_cast<float>(g) / aRight);
		b = static_cast<int>(static_cast<float>(b) / aRight);
		a = static_cast<int>(static_cast<float>(a) / aRight);
		return *this;
	}

	Color Color::Blend(const Color &aTo, float aProgress)
	{
		return Blend(*this, aTo, aProgress);
	}

	Color Color::Blend(const Color &aFrom, const Color &aTo, float aProgress)
	{
		return aFrom + (aTo - aFrom) * aProgress;
	}
}
