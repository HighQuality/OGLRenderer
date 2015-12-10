#include "OpenGLTexture.h"
#include <SDL_image.h>
#include <string>

OpenGLTexture::OpenGLTexture(const std::string &fileName)
{
	glGenTextures(1, &myTextureHandle);
	glBindTexture(GL_TEXTURE_2D, myTextureHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	SDL_Surface* surface = IMG_Load(fileName.c_str());

	myWidth = surface->w;
	myHeight = surface->h;

	int mode = GL_RGB;

	if (surface->format->BytesPerPixel == 4) {
		mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);
}

Cog::Vector2ui OpenGLTexture::GetSize() const
{
	return Cog::Vector2ui(myWidth, myHeight);
}

void OpenGLTexture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, myTextureHandle);
}

OpenGLTexture::~OpenGLTexture()
{
	glDeleteTextures(1, &myTextureHandle);
	myTextureHandle = 0;
}
