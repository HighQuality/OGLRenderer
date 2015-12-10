#include "Engine.h"
#include "RendererModule.h"
#include "EventHost.h"
#include "InitializeEvent.h"
#include "Window.h"

namespace Cog
{
	bool Engine::myIsInitialized = false;
	bool Engine::myGameIsRunning = false;
	RendererModule *Engine::myRenderer = nullptr;
	EventHost *Engine::myEventHost = nullptr;
	EngineDeinitializer Engine::myDeinitializer;
	
	void Engine::InnerInitialize()
	{
		myEventHost = new EventHost();
		myIsInitialized = true;
	}

	void Engine::Destruct()
	{
		if (myIsInitialized)
		{
			delete myRenderer;
			myRenderer = nullptr;

			delete myEventHost;
			myEventHost = nullptr;

			myIsInitialized = false;
		}
	}

	void Engine::StartGame()
	{
		myGameIsRunning = true;

		// Create a hidden window and a graphics context
		myRenderer->CreateHiddenWindowAndContext();

		myEventHost->TriggerEvent(InitializeEvent());

		// Show the window
		myRenderer->GetWindow()->SetVisible(true);

		while (myGameIsRunning = true)
		{
			myRenderer->TriggerEvents();

			myRenderer->Clear();

			myRenderer->PresentBackBuffer();
		}
	}

	RendererModule *Engine::GetRenderer()
	{
		return myRenderer;
	}

	EventHost *Engine::GetEventHost()
	{
		return myEventHost;
	}

	Engine::Engine()
	{
	}
}
