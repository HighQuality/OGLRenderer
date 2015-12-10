#include "SceneHost.h"
#include "GameScene.h"

namespace Cog
{
	SceneHost::SceneHost()
	{
	}

	SceneHost::~SceneHost()
	{
		while (myScenes.size() > 0)
		{
			PopAndDelete();
		}
	}

	GameScene *SceneHost::GetCurrentScene() const
	{
		if (myScenes.size() == 0)
		{
			return nullptr;
		}
		return myScenes[myScenes.size() - 1];
	}

	void SceneHost::Push(GameScene *aGameScene)
	{
		myScenes.push_back(aGameScene);
	}

	GameScene *SceneHost::Pop()
	{
		GameScene *scene = myScenes[myScenes.size() - 1];
		myScenes.erase(myScenes.begin() + (myScenes.size() - 1));
		return scene;
	}

	void SceneHost::PopAndDelete()
	{
		delete Pop();
	}
}