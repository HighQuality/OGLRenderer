#pragma once

namespace Cog
{
	class IGameObject;
	class GameObjectComponent
	{
	public:
		GameObjectComponent(IGameObject &aGameObject);
		virtual ~GameObjectComponent();

	protected:
		IGameObject *myObject;
	};
}
