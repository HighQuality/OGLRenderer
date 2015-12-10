#pragma once
#include "Color.h"

namespace Cog
{
	class Image
	{
	public:
		Image();
		void SetPixel(int x, int y, const Color &aColor);
		Color GetPixel() const;
		virtual ~Image();
	};
}
