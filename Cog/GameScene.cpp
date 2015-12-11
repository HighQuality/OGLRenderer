#include "GameScene.h"
#include "IGameObject.h"
#include "CameraObject.h"

namespace Cog
{
	GameScene::GameScene()
	{
		myCamera = AddObject(new CameraObject());
	}
	
	CameraObject &GameScene::GetCamera() const
	{
		return *myCamera;
	}

	GameScene::~GameScene()
	{
		for (size_t i = 0; i < myObjects.size(); i++)
		{
			delete myObjects[i];
		}
		myObjects.clear();
	}
}
