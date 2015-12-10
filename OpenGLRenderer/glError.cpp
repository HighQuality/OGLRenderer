#include "glError.h"

void CheckError()
{
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		std::cout << glewGetErrorString(error) << "(" << error << ")" << std::endl;
	}
}