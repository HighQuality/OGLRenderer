#include "Engine.h"
#include "RendererModule.h"
#include "EventHost.h"
#include "UpdateEvent.h"
#include "DrawEvent.h"
#include "SceneHost.h"
#include "CloseButtonPressedEvent.h"
#include "Window.h"
#include "Stopwatch.h"
#include "ExitingEvent.h"
#include "ThreadPool.h"
#include "WorkItem.h"
#include "RenderTarget.h"
#include "EndUpdateEvent.h"
#include "Matrix33.h"
#include "Transformation.h"
#include "GameScene.h"
#include "CameraObject.h"

namespace Cog
{
	bool Engine::myIsInitialized = false;
	bool Engine::myGameIsRunning = false;
	RendererModule *Engine::myRenderer = nullptr;
	EventHost *Engine::myEventHost = nullptr;
	SceneHost *Engine::mySceneHost = nullptr;
	ThreadPool *Engine::myThreadPool = nullptr;
	std::vector<RenderCommand> *Engine::myNewRenderCommands = nullptr;
	EngineDeinitializer Engine::myDeinitializer;
	float Engine::myTimeAccumulator = 0.f,
		Engine::myTimeStep = 1.f / 15.f;
	
	void Engine::InnerInitialize()
	{
		myEventHost = new EventHost();
		mySceneHost = new SceneHost();
		myThreadPool = new ThreadPool();
		myNewRenderCommands = new std::vector<RenderCommand>();

		// Create a hidden window and a graphics context
		myRenderer->CreateHiddenWindowAndContext();

		myIsInitialized = true;
	}

	void Engine::Destruct()
	{
		if (myIsInitialized)
		{
			delete myRenderer;
			myRenderer = nullptr;

			delete mySceneHost;
			mySceneHost = nullptr;

			delete myEventHost;
			myEventHost = nullptr;

			delete myThreadPool;
			myThreadPool = nullptr;

			delete myNewRenderCommands;
			myNewRenderCommands = nullptr;

			myIsInitialized = false;
		}
	}

	void Engine::StartGame()
	{
		myGameIsRunning = true;

		// Close the game when we hit the close button
		myEventHost->RegisterEvent<CloseButtonPressedEvent>([=](CloseButtonPressedEvent &ev)
		{
			myGameIsRunning = false;
		});

		// Show the window
		myRenderer->GetWindow()->SetVisible(true);

		Stopwatch stopwatch;
		std::vector<RenderCommand> *currentRenderCommands = new std::vector<RenderCommand>();

		float time = 0.f;

		while (myGameIsRunning == true)
		{
			float deltaTime = stopwatch.GetElapsedSeconds();
			time += deltaTime;
			stopwatch.Restart();

			myRenderer->TriggerEvents();

			std::swap(currentRenderCommands, myNewRenderCommands);

			float progressToNextFixedUpdate = (myTimeAccumulator / myTimeStep);

			myTimeAccumulator += deltaTime;

			Matrix33f worldToViewport;
			Transformation cameraTransformation = mySceneHost->GetCurrentScene()->GetCamera().GetTransformation();

			auto gameLogicWork = myThreadPool->QueueWorkItem(std::function<void()>([=]
			{
				while (myTimeAccumulator >= myTimeStep)
				{
					myEventHost->TriggerEvent(UpdateEvent(myTimeStep));
					myEventHost->TriggerEvent(EndUpdateEvent());
					myTimeAccumulator -= myTimeStep;
				}

				myEventHost->TriggerEvent(DrawEvent());
			}));

			Vector2f windowSize = Vector2f(myRenderer->GetWindow()->GetSize());
			worldToViewport *= Matrix33f::CreateScale(2.f / windowSize.x, -2.f / windowSize.y, 1.f) * Matrix33f::CreateTranslation(-cameraTransformation.Position.x, -cameraTransformation.Position.y) * Matrix33f::CreateRotateAroundZ(cameraTransformation.Rotation);

			myRenderer->SetWorldToViewportMatrix(worldToViewport);

			myRenderer->Clear();
			RenderTarget &renderTarget = *myRenderer->GetRenderTarget();
			
			for (size_t i = 0; i < currentRenderCommands->size(); i++)
			{
				RenderCommand currentCommand = (*currentRenderCommands)[i];

				Vector2f position = currentCommand.previousPosition + (currentCommand.currentPosition - currentCommand.previousPosition) * progressToNextFixedUpdate;

				renderTarget.Render(currentCommand.texture, position);
			}
			currentRenderCommands->clear();

			myRenderer->PresentBackBuffer();

			float beginSleep = stopwatch.GetElapsedSeconds();
			std::this_thread::sleep_for(std::chrono::microseconds(1));

			// Wait for the game logic update to finish
			gameLogicWork->Wait();

			if (mySceneHost->GetCurrentScene() == nullptr)
			{
				myGameIsRunning = false;
			}
		}

		delete currentRenderCommands;

		myEventHost->TriggerEvent(ExitingEvent());
	}

	RendererModule *Engine::GetRenderer()
	{
		return myRenderer;
	}

	EventHost *Engine::GetEventHost()
	{
		return myEventHost;
	}

	SceneHost *Engine::GetSceneHost()
	{
		return mySceneHost;
	}

	ThreadPool *Engine::GetThreadPool()
	{
		return myThreadPool;
	}

	void Engine::ScheduleRendering(const RenderCommand &aRenderCommand)
	{
		myNewRenderCommands->push_back(aRenderCommand);
	}

	bool Engine::IsInitialized()
	{
		return myIsInitialized;
	}
	
	Engine::Engine()
	{
	}
}
