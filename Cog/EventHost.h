#pragma once

namespace Cog
{
	class EventHost
	{
	public:
		EventHost();
		~EventHost();

		template <typename TEventType, typename TEventCatcher>
		void RegisterEvent(TEventCatcher &aCatcher);

		template <typename TEventType>
		void TriggerEvent(const TEventType &aEvent);
	};

	template <typename TEventType, typename TEventCatcher>
	void EventHost::RegisterEvent(TEventCatcher &aCatcher)
	{

	}

	template <typename TEventType>
	void EventHost::TriggerEvent(const TEventType &aEvent)
	{

	}
}
