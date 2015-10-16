#pragma once
#include <GL/glew.h>
#include <string>

class Texture
{
public:
	Texture(const std::string &fileName);

	void Bind() const;

	~Texture();

	GLuint textureHandle;
	int width;
	int height;
};
