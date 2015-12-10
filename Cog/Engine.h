#pragma once
#include "EngineDeinitializer.h"

namespace Cog
{
	class EventHost;
	class RendererModule;
	class Window;

	class Engine
	{
	public:
		template<typename TRendererModule>
		static void Initialize();
		static void Destruct();

		static void StartGame();

		static RendererModule *GetRenderer();
		static EventHost *GetEventHost();

	private:
		// Disable object instantiation
		Engine();
		static RendererModule *myRenderer;
		static EventHost *myEventHost;
		static EngineDeinitializer myDeinitializer;
		static bool myIsInitialized,
			myGameIsRunning;

		static void InnerInitialize();
	};
	
	template<typename TRendererModule>
	void Engine::Initialize()
	{
		myRenderer = new TRendererModule();
		InnerInitialize();
	}
}
