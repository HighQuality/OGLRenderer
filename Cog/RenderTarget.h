#pragma once
#include "Vector.h"

namespace Cog
{
	class Texture;
	class RenderTarget
	{
	public:
		RenderTarget();
		virtual ~RenderTarget();

		virtual void Render(Texture *aTexture, Vector2f aPosition) = 0;
	};
}
