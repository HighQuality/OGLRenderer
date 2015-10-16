#pragma once

#include "Texture.h"
#include "Vector3.h"

struct Sprite
{
public:
	Texture *texture;
	Vector2 position;
	Vector2 origin;
	Vector4 color;
	Vector2 scale;
	Vector2 texRectPosition;
	Vector2 texRectSize;
	float rotation;

	Sprite()
	{
		color = Vector4(1.f, 1.f, 1.f, 1.f);
		texRectSize = Vector2(1.f, 1.f);
		scale = Vector2(1.f, 1.f);
		rotation = 0.f;
	}
};
