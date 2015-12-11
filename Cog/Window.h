#pragma once
#include "Vector.h"

namespace Cog
{
	class Window
	{
	public:
		virtual ~Window();

		virtual Vector2ui GetSize() const = 0;
		virtual void SetVisible(bool aIsVisible) = 0;

	protected:
		Window();
	};
}
