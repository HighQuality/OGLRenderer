// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Engine.h>
#include <OpenGLRenderer.h>
#include <EventHost.h>
#include <SceneHost.h>
#include <iostream>
#include "MainScene.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Cog::Engine::Initialize<OpenGLRenderer>();

	// Initialize the game
	Cog::Engine::GetSceneHost()->Push(new MainScene());

	// Start it
	Cog::Engine::StartGame();

	return 0;
}

