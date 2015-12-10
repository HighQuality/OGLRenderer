#pragma once
#include <RendererModule.h>
#include <Window.h>

struct SDL_Window;
typedef void* SDL_GLContext;

class OpenGLRenderer : public Cog::RendererModule, public Cog::Window
{
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	// Renderer abstract functions
	Cog::Window *CreateHiddenWindowAndContext();
	Cog::Window *GetWindow();

	void TriggerEvents();
	void Clear();
	void PresentBackBuffer();

	// Window abstract functions
	Cog::Vector2ui GetSize() const;
	void SetVisible(bool aIsVisible);

private:
	SDL_Window *myWindow;
	SDL_GLContext myContext;
};
