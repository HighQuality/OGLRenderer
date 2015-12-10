#pragma once

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <GL/glew.h>

using Vector2 = Cog::Vector2f;
using Vector3 = Cog::Vector3f;
using Vector4 = Cog::Vector4f;

struct Vertex
{
	Vector2 Position;
	Vector2 TexCoord;
	Vector4 Color;

	Vertex()
	{
	}

	Vertex(Vector2 position, Vector2 texCoord, Vector4 color)
	{
		Position = position;
		TexCoord = texCoord;
		Color = color;
	}

	static void SetAttribPointers()
	{
		Vertex vertex;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 8, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float) * 2));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float) * 4));
	}
};
