#pragma once
#include "Vector4.h"

namespace Cog
{
	class Color
	{
	public:
		Color(void);

		Color(const Color &anOther);

		Color(int red, int green, int blue, int alpha);

		Color(int red, int green, int blue);

		Vector4f ToVector4();

		Color &operator =(const Color &aRight);

		Color &operator +=(const Color &aRight);
		Color &operator -=(const Color &aRight);
		Color &operator *=(float aRight);
		Color &operator /=(const float aRight);

		Color Blend(const Color &aTo, float aProgress);

		static Color Blend(const Color &aFrom, const Color &aTo, float aProgress);

		int r,
			g,
			b,
			a;

		static const Color White,
			CornflowerBlue,
			Red,
			Green,
			Blue,
			Gray,
			Black,
			Yellow,
			Purple,
			Cyan;
	};

	Color operator +(Color aLeft, const Color &aRight);

	Color operator -(Color aLeft, const Color &aRight);

	Color operator *(Color aLeft, const Color aRight);

	Color operator /(Color aLeft, const Color aRight);

	Color operator *(Color aLeft, const float aRight);

	Color operator /(Color aLeft, const float aRight);

	bool operator ==(const Color &aLeft, const Color &aRight);

	bool operator !=(const Color &aLeft, const Color &aRight);

}
