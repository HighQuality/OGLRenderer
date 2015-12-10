// SDLOpenGL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "GLBuffer.h"
#include "Vertex.h"
#include "Shader.h"
#include "glError.h"
#include <vector>
#include <SDL_image.h>
#include "Texture.h"
#include "SpriteBatch.h"
#include "Sprite.h"
#include "Stopwatch.h"
#include <random>
#include "Keyboard.h"

int _tmain(int argc, _TCHAR* argv[])
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
	SDL_WindowFlags flags = (SDL_WindowFlags)(SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	
	SDL_Window *win = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resolutionWidth, resolutionHeight, flags);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GLContext context = SDL_GL_CreateContext(win);
	if (context == nullptr)
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
	
	{
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Cornflower blue ftw
		glClearColor(100.f / 255.f, 149.f / 255.f, 237.f / 255.f, 255.f);

		Shader shader;

		Texture texture("texture.png");
		Texture anotherTexture("texture2.png");

		SpriteBatch batch;

		Stopwatch watch;
		Keyboard keyboard;

		bool isOpen = true;
		while (isOpen)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event) == 1)
			{
				if (event.type == SDL_QUIT)
				{
					isOpen = false;
				}
				else if (event.type == SDL_KEYDOWN)
				{
					if (event.key.repeat == 0)
					{
						keyboard.KeyDown(event.key.keysym.sym);
					}
				}
				else if (event.type == SDL_KEYUP)
				{
					keyboard.KeyUp(event.key.keysym.sym);
				}
			}

			batch.viewPosition = Vector2();
			int w,
				h;
			SDL_GetWindowSize(win, &w, &h);
			batch.viewSize = Vector2(static_cast<float>(w), static_cast<float>(h));
			glViewport(0, 0, w, h);

			shader.Use();
			glActiveTexture(GL_TEXTURE0);

			glClear(GL_COLOR_BUFFER_BIT);

			Sprite sprite;
			sprite.texture = &texture;
			sprite.origin = Vector2(static_cast<float>(sprite.texture->width) / 2.f, static_cast<float>(sprite.texture->height) / 2.f);
			sprite.position = Vector2(320, 240);
			batch.Draw(sprite);

			sprite.texture = &anotherTexture;
			sprite.position = Vector2(16, 16);
			sprite.origin = Vector2();
			batch.Draw(sprite);

			// Draw undrawn sprites in the batch
			batch.DrawBuffer();

			SDL_GL_SwapWindow(win);
		}
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}

