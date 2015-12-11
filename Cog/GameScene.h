#pragma once
#include <vector>

namespace Cog
{
	class IGameObject;
	class CameraObject;

	class GameScene
	{
	public:
		GameScene();
		virtual ~GameScene();

		template<typename T>
		T *AddObject(T *aObject)
		{
			myObjects.push_back(aObject);
			return aObject;
		}

		CameraObject &GetCamera() const;

	private:
		std::vector<IGameObject*> myObjects;
		CameraObject *myCamera;
	};
}
