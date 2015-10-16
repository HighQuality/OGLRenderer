#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{
public:
	Shader();
	void Use();
	~Shader();

	GLuint program;
};
