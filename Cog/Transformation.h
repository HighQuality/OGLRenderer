#pragma once
#include "Vector2.h"

namespace Cog
{
	class Transformation
	{
	public:
		Transformation()
			: Scale(1.f, 1.f)
		{
			Rotation = 0.f;
		}

		Vector2f Position;
		Vector2f Scale;
		float Rotation;
	};
}
