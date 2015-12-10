#pragma once
#include "EngineDeinitializer.h"
#include "RenderCommand.h"
#include <vector>

namespace Cog
{
	class EventHost;
	class SceneHost;
	class RendererModule;
	class Window;
	class ThreadPool;

	class Engine
	{
	public:
		template<typename TRendererModule>
		static void Initialize();
		static void Destruct();

		static void StartGame();

		static RendererModule *GetRenderer();
		static EventHost *GetEventHost();
		static SceneHost *GetSceneHost();
		static void ScheduleRendering(const RenderCommand &aRenderCommand);

	private:
		// Disable object instantiation
		Engine();
		static RendererModule *myRenderer;
		static EventHost *myEventHost;
		static SceneHost *mySceneHost;
		static ThreadPool *myThreadPool;
		static float myTimeAccumulator;
		static float myTimeStep;
		static EngineDeinitializer myDeinitializer;
		static bool myIsInitialized,
			myGameIsRunning;

		static std::vector<RenderCommand>* myNewRenderCommands;

		static void InnerInitialize();
	};
	
	template<typename TRendererModule>
	void Engine::Initialize()
	{
		myRenderer = new TRendererModule();
		InnerInitialize();
	}
}
