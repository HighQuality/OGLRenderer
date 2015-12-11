#pragma once
#include "Vector.h"

namespace Cog
{
	class Texture;

	class RenderCommand
	{
	public:
		Texture *texture;
		Vector2f previousPosition,
			currentPosition;
	};
}
