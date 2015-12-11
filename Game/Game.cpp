// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Engine.h>
#include <OpenGLRenderer.h>
#include <EventHost.h>
#include <SceneHost.h>
#include <iostream>
#include "MainScene.h"
#include <Matrix.h>

template class Cog::Matrix<4, 4, float>;
template class Cog::Matrix<4, 4, double>;

template class Cog::Matrix<3, 3, float>;
template class Cog::Matrix<3, 3, double>;

int _tmain(int argc, _TCHAR* argv[])
{
	Cog::Engine::Initialize<OpenGLRenderer>();

	// Initialize the game
	Cog::Engine::GetSceneHost()->Push(new MainScene());

	// Start it
	Cog::Engine::StartGame();

	// De-initialize the engine and free all memory allocated by it
	Cog::Engine::Destruct();

	return 0;
}

