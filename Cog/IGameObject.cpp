#include "IGameObject.h"
#include "IEventListener.h"

namespace Cog
{
	IGameObject::IGameObject()
	{
	}

	IGameObject::~IGameObject()
	{
		myScene = nullptr;

		for (size_t i = 0; i < myListeners.size(); i++)
		{
			myListeners[i]->StopListen();
		}
	}

	GameScene &IGameObject::GetGenericScene() const
	{
		return *myScene;
	}
}
