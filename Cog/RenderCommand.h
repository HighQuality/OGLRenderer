#pragma once
#include "Vector2.h"

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
