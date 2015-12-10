#pragma once
#include "EventCollection.h"

namespace Cog
{
	class EventHost
	{
	public:
		EventHost();
		~EventHost();

		template <typename TEventType, typename TEventCatcher>
		EventListener<TEventType> RegisterEvent(TEventCatcher &aCatcher);

		template <typename TEventType>
		void TriggerEvent(TEventType &aEvent);
	};

	template <typename TEventType, typename TEventCatcher>
	EventListener<TEventType> EventHost::RegisterEvent(TEventCatcher &aCatcher)
	{
		return EventCollection<TEventType>::RegisterEvent(aCatcher);
	}

	template <typename TEventType>
	void EventHost::TriggerEvent(TEventType &aEvent)
	{
		EventCollection<TEventType>::TriggerEvent(aEvent);
	}
}
