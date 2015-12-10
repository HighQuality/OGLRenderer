#include "GameObjectComponent.h"

namespace Cog
{
	GameObjectComponent::GameObjectComponent(IGameObject &aGameObject)
	{
		myObject = &aGameObject;
	}

	GameObjectComponent::~GameObjectComponent()
	{
	}
}
