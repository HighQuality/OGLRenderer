#pragma once
#include <RendererModule.h>
#include <Window.h>
#include <RenderTarget.h>

struct SDL_Window;
typedef void* SDL_GLContext;

namespace Cog
{
	template<typename T>
	class Matrix33;
	class Texture;
}

class Shader;
class SpriteBatch;

class OpenGLRenderer : public Cog::RendererModule, public Cog::Window, public Cog::RenderTarget
{
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	// Renderer abstract functions
	Cog::Window *CreateHiddenWindowAndContext();
	Cog::Window *GetWindow();
	Cog::RenderTarget *GetRenderTarget();

	Cog::Texture *LoadTexture(const char *aFileName);

	void SetWorldToViewportMatrix(Cog::Matrix33<float> &aWorldToViewportMatrix);
	void Render(Cog::Texture *aTexture, Cog::Vector2f aPosition);

	void TriggerEvents();
	void Clear();
	void PresentBackBuffer();

	// Window abstract functions
	Cog::Vector2ui GetSize() const;
	void SetVisible(bool aIsVisible);

private:
	SDL_Window *myWindow;
	SDL_GLContext myContext;
	SpriteBatch *mySpriteBatch;
	Shader *myDefaultShader;
};
