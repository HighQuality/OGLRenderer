#pragma once
#include <functional>
#include <vector>
#include "Vector2.h"
#include "EventHost.h"
#include "Transformation.h"

namespace Cog
{
	template <typename TSceneType>
	class GameObject;
	class GameScene;
	class IEventListener;
	template <typename TEventType>
	class EventListener;

	class IGameObject
	{
	public:
		IGameObject();
		virtual ~IGameObject();

		template<typename TEventType, typename TObjectType>
		EventListener<TEventType> &RegisterEvent(void (TObjectType::*aCatcher)(TEventType&), TObjectType *anObject)
		{
			EventListener<TEventType> &listener = Engine::GetEventHost()->RegisterEvent<TEventType>([=](TEventType &ev)
			{
				(anObject->*aCatcher)(ev);
			});
			myListeners.push_back(&listener);
			return listener;
		}

		template<typename TEventType, typename TEventCatcher>
		EventListener<TEventType> RegisterEvent(TEventCatcher &eventCatcher)
		{
			EventListener<TEventType> &listener = Engine::GetEventHost()->RegisterEvent<TEventType>(eventCatcher);
			myListeners.push_back(&listener);
			return listener;
		}

		GameScene &GetGenericScene() const;

		inline void SetPosition(Vector2f aPosition)
		{
			myTransformation.Position = aPosition;
		}
		inline Vector2f GetPosition() const
		{
			return myTransformation.Position;
		}

		const Transformation &GetTransformation() const
		{
			return myTransformation;
		}

	private:
		template <typename TSceneType>
		friend class GameObject;

		std::vector<IEventListener*> myListeners;

		GameScene *myScene;
		Transformation myTransformation;
	};
}
