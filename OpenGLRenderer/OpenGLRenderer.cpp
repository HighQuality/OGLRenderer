#include "OpenGLRenderer.h"
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_image.h>

OpenGLRenderer::OpenGLRenderer()
{

}

OpenGLRenderer::~OpenGLRenderer()
{
	SDL_GL_DeleteContext(myContext);
	SDL_DestroyWindow(myWindow);
	SDL_Quit();
	
	myContext = nullptr;
	myWindow = nullptr;
}

Cog::Window *OpenGLRenderer::CreateHiddenWindowAndContext()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_INIT error: " << SDL_GetError() << std::endl;
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "IMG_Init error: " << IMG_GetError() << std::endl;
	}

	std::string windowTitle = "Hello World!";
	int resolutionWidth = 1280;
	int resolutionHeight = 720;
	SDL_WindowFlags flags = (SDL_WindowFlags)(SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);

	myWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resolutionWidth, resolutionHeight, flags);
	if (myWindow == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return nullptr;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	myContext = SDL_GL_CreateContext(myWindow);
	if (myContext == nullptr)
	{
		std::cout << "SDL_GL_CreateContext error: " << SDL_GetError() << std::endl;
	}

	GLenum glewError = glewInit();

	if (glewError != GLEW_OK)
	{
		std::cout << "glewInit() failed: " << glewGetErrorString(glewError) << std::endl;
	}

	//Use Vsync
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return this;
}

Cog::Window *OpenGLRenderer::GetWindow()
{
	return this;
}

void OpenGLRenderer::TriggerEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) == 1)
	{
		if (event.type == SDL_QUIT)
		{
			// TODO: Send Cog::CloseButtonPressed
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.repeat == 0)
			{
				// TODO: Send Cog::KeyDownEvent
			}
			else
			{
				// TODO: Send Cog::KeyRepeatEvent
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			// TODO: Send Cog::KeyUpEvent
		}
	}
}

void OpenGLRenderer::Clear()
{
	Cog::Vector4f clearColor = GetBackgroundColor().ToVector4();
	glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::PresentBackBuffer()
{
	SDL_GL_SwapWindow(myWindow);
}

Cog::Vector2ui OpenGLRenderer::GetSize() const
{
	return Cog::Vector2ui();
}

void OpenGLRenderer::SetVisible(bool aIsVisible)
{
	if (aIsVisible)
	{
		SDL_ShowWindow(myWindow);
	}
	else
	{
		SDL_HideWindow(myWindow);
	}
}
