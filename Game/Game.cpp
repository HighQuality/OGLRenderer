// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Engine.h>
#include <OpenGLRenderer.h>
#include <EventHost.h>
#include <InitializeEvent.h>

int _tmain(int argc, _TCHAR* argv[])
{
	Cog::Engine::Initialize<OpenGLRenderer>();

	Cog::Engine::GetEventHost()->RegisterEvent<Cog::InitializeEvent>([] (const Cog::InitializeEvent &ev)
	{
		
	});

	Cog::Engine::StartGame();

	return 0;
}

