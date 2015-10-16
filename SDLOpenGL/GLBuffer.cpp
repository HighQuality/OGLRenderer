#include "GLBuffer.h"

GLBuffer::GLBuffer()
{
	glGenBuffers(1, &glBufferIndex);
}

void GLBuffer::Bind(GLenum target) const
{
	glBindBuffer(target, glBufferIndex);
}

GLBuffer::~GLBuffer()
{
	glDeleteBuffers(1, &glBufferIndex);
}
