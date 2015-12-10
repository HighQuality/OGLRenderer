#pragma once
#include <vector>

namespace Cog
{
	class IGameObject;

	class GameScene
	{
	public:
		GameScene();
		virtual ~GameScene();

		void AddObject(IGameObject *aObject);

	private:
		std::vector<IGameObject*> myObjects;
	};
}
