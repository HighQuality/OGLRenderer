#pragma once
#include "Vector.h"

namespace Cog
{
	class Texture
	{
	public:
		Texture();
		virtual ~Texture();
		virtual Vector2ui GetSize() const = 0;
	};
}
