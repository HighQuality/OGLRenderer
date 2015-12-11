#pragma once
#include <functional>
#include <vector>
#include "Vector.h"
#include "EventHost.h"

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
			myPosition = aPosition;
		}
		inline Vector2f GetPosition() const
		{
			return myPosition;
		}

	private:
		template <typename TSceneType>
		friend class GameObject;

		std::vector<IEventListener*> myListeners;

		GameScene *myScene;
		Vector2f myPosition;
	};
}
