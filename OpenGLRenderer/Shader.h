#pragma once

#include <string>
#include <GL/glew.h>

namespace Cog
{
	template<typename T>
	class Matrix33;
}

class Shader
{
public:
	Shader();
	void Use();
	void SetMatrix(const char *aUniformName, Cog::Matrix33<float> &aMatrix);
	~Shader();

	GLuint program;
};
