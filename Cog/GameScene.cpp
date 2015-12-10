#include "GameScene.h"
#include "IGameObject.h"

namespace Cog
{
	GameScene::GameScene()
	{
	}

	GameScene::~GameScene()
	{
		for (size_t i = 0; i < myObjects.size(); i++)
		{
			delete myObjects[i];
		}
		myObjects.clear();
	}

	void GameScene::AddObject(IGameObject *aObject)
	{
		myObjects.push_back(aObject);
	}
}
