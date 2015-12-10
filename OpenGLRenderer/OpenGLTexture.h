#pragma once
#include <GL/glew.h>
#include <string>
#include <Texture.h>
#include <Vector2.h>

class OpenGLTexture : public Cog::Texture
{
public:
	OpenGLTexture(const std::string &fileName);

	void Bind() const;
	Cog::Vector2ui GetSize() const;

	~OpenGLTexture();

private:
	friend class SpriteBatch;
	GLuint myTextureHandle;
	int myWidth;
	int myHeight;
};
