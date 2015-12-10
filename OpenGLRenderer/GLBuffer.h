#pragma once
#include <GL/glew.h>

class GLBuffer
{
public:
	GLBuffer();
	void Bind(GLenum target) const;
	~GLBuffer();
	GLuint glBufferIndex;
};
