#include "SpriteBatch.h"
#include <math.h>
#define PI 3.14159265358979323846

SpriteBatch::SpriteBatch()
{
	buffer.Bind(GL_ARRAY_BUFFER);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 1024, vertices, GL_DYNAMIC_DRAW);
	Vertex::SetAttribPointers();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	currentTexture = -1;
	nextVertexIndex = 0;
}

void SpriteBatch::Draw(const Sprite &sprite)
{
	if (currentTexture == -1)
	{
		currentTexture = sprite.texture->textureHandle;
	}
	if (nextVertexIndex + 4 > 1024 || sprite.texture->textureHandle != currentTexture)
	{
		DrawBuffer();
		currentTexture = sprite.texture->textureHandle;
	}

	Vector2 origin = Vector2(sprite.origin.X * sprite.scale.X, sprite.origin.Y * sprite.scale.Y);
	
	float rotation = sprite.rotation / 180.f * (float)PI;

	float rX = sprite.texRectPosition.X,
		rY = sprite.texRectPosition.Y,
		rW = sprite.texRectSize.X,
		rH = sprite.texRectSize.Y;

	int width = sprite.texture->width;
	int height = sprite.texture->height;

	Vector2 topLeft = Vector2(-origin.X, -origin.Y);
	Vector2 topRight = Vector2(-origin.X + width * sprite.scale.X, -origin.Y);
	Vector2 bottomRight = Vector2(-origin.X + width * sprite.scale.X, -origin.Y + height * sprite.scale.Y);
	Vector2 bottomLeft = Vector2(-origin.X, -origin.Y + height * sprite.scale.Y);
	
	float sin = (float)std::sin(rotation);
	float cos = (float)std::cos(rotation);

	topLeft = Vector2(topLeft.X * cos - topLeft.Y * sin, topLeft.X * sin + topLeft.Y * cos);
	topRight = Vector2(topRight.X * cos - topRight.Y * sin, topRight.X * sin + topRight.Y * cos);
	bottomRight = Vector2(bottomRight.X * cos - bottomRight.Y * sin, bottomRight.X * sin + bottomRight.Y * cos);
	bottomLeft = Vector2(bottomLeft.X * cos - bottomLeft.Y * sin, bottomLeft.X * sin + bottomLeft.Y * cos);
	
	topLeft.X += sprite.position.X;
	topLeft.Y += sprite.position.Y;
	bottomLeft.X += sprite.position.X;
	bottomLeft.Y += sprite.position.Y;
	topRight.X += sprite.position.X;
	topRight.Y += sprite.position.Y;
	bottomRight.X += sprite.position.X;
	bottomRight.Y += sprite.position.Y;
	
	topLeft.X = (topLeft.X / viewSize.X * 2.f) - 1.f;
	topLeft.Y = -1.f * ((topLeft.Y / viewSize.Y * 2.f) - 1.f);

	topRight.X = (topRight.X / viewSize.X * 2.f) - 1.f;
	topRight.Y = -1.f * ((topRight.Y / viewSize.Y * 2.f) - 1.f);

	bottomRight.X = (bottomRight.X / viewSize.X * 2.f) - 1.f;
	bottomRight.Y = -1.f * ((bottomRight.Y / viewSize.Y * 2.f) - 1.f);

	bottomLeft.X = (bottomLeft.X / viewSize.X * 2.f) - 1.f;
	bottomLeft.Y = -1.f * ((bottomLeft.Y / viewSize.Y * 2.f) - 1.f);

	vertices[nextVertexIndex++] = Vertex(topLeft, Vector2(rX, rY), sprite.color);
	vertices[nextVertexIndex++] = Vertex(topRight, Vector2(rX + rW, rY), sprite.color);
	vertices[nextVertexIndex++] = Vertex(bottomRight, Vector2(rX + rW, rY + rH), sprite.color);
	vertices[nextVertexIndex++] = Vertex(bottomLeft, Vector2(rX, rY + rH), sprite.color);
}

void SpriteBatch::DrawBuffer()
{
	buffer.Bind(GL_ARRAY_BUFFER);
	
	glBindTexture(GL_TEXTURE_2D, currentTexture);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * nextVertexIndex, vertices);
	Vertex::SetAttribPointers();
	glDrawArrays(GL_QUADS, 0, nextVertexIndex);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	nextVertexIndex = 0;
	currentTexture = -1;
}

SpriteBatch::~SpriteBatch()
{

}
