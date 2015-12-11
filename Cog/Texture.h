#pragma once
#include "Vector2.h"

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
