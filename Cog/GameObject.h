#pragma once
#include "IGameObject.h"

namespace Cog
{
	template<typename TSceneType>
	class GameObject : public IGameObject
	{
	public:
		GameObject()
		{
		}

		~GameObject()
		{
		}

		inline TSceneType &GetScene() const;
	};

	template<typename TSceneType>
	TSceneType &GameObject<TSceneType>::GetScene() const
	{
		return *static_cast<TSceneType*>(myScene);
	}
}
