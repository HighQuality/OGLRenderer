#pragma once
#include <vector>

namespace Cog
{
	class GameScene;

	class SceneHost
	{
	public:
		SceneHost();
		~SceneHost();

		GameScene *GetCurrentScene() const;
		void Push(GameScene *aGameScene);
		GameScene *Pop();
		void PopAndDelete();

	private:
		std::vector<GameScene*> myScenes;
	};
}
