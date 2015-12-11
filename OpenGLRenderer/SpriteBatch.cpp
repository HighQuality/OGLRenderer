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
		currentTexture = sprite.texture->myTextureHandle;
	}
	if (nextVertexIndex + 4 > 1024 || sprite.texture->myTextureHandle != currentTexture)
	{
		DrawBuffer();
		currentTexture = sprite.texture->myTextureHandle;
	}

	Vector2 origin = Vector2(sprite.origin.x * sprite.scale.x, sprite.origin.y * sprite.scale.y);
	
	float rotation = sprite.rotation / 180.f * (float)PI;

	float rX = sprite.texRectPosition.x,
		rY = sprite.texRectPosition.y,
		rW = sprite.texRectSize.x,
		rH = sprite.texRectSize.y;

	int width = sprite.texture->myWidth;
	int height = sprite.texture->myHeight;

	Vector2 topLeft = Vector2(-origin.x, -origin.y);
	Vector2 topRight = Vector2(-origin.x + width * sprite.scale.x, -origin.y);
	Vector2 bottomRight = Vector2(-origin.x + width * sprite.scale.x, -origin.y + height * sprite.scale.y);
	Vector2 bottomLeft = Vector2(-origin.x, -origin.y + height * sprite.scale.y);
	
	const float sin = static_cast<float>(std::sin(rotation));
	const float cos = static_cast<float>(std::cos(rotation));

	topLeft = Vector2(topLeft.x * cos - topLeft.y * sin, topLeft.x * sin + topLeft.y * cos);
	topRight = Vector2(topRight.x * cos - topRight.y * sin, topRight.x * sin + topRight.y * cos);
	bottomRight = Vector2(bottomRight.x * cos - bottomRight.y * sin, bottomRight.x * sin + bottomRight.y * cos);
	bottomLeft = Vector2(bottomLeft.x * cos - bottomLeft.y * sin, bottomLeft.x * sin + bottomLeft.y * cos);
	
	topLeft.x += sprite.position.x;
	topLeft.y += sprite.position.y;
	bottomLeft.x += sprite.position.x;
	bottomLeft.y += sprite.position.y;
	topRight.x += sprite.position.x;
	topRight.y += sprite.position.y;
	bottomRight.x += sprite.position.x;
	bottomRight.y += sprite.position.y;
	
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
