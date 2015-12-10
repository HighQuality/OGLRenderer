#pragma once

#include "Texture.h"
#include <vector>
#include "Vertex.h"
#include "Sprite.h"
#include "GLBuffer.h"

class SpriteBatch
{
public:
	SpriteBatch();

	void Draw(const Sprite &sprite);
	void DrawBuffer();

	~SpriteBatch();

	Vector2 viewPosition,
		viewSize;

private:
	GLBuffer buffer;
	Vertex vertices[1024];
	int nextVertexIndex;
	GLuint currentTexture;
};
