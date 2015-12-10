#pragma once
#include "Vector2.h"

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
