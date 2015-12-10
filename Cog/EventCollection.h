#pragma once
#include <vector>
#include <functional>
#include "EventListener.h"

namespace Cog
{
	template <typename TEventType>
	class EventCollection
	{
	public:
		template <typename TEventCatcher>
		static EventListener<TEventType> &RegisterEvent(TEventCatcher &aCatcher)
		{
			myListeners.push_back(EventListener<TEventType>());
			myListeners[myListeners.size() - 1].SetCatcher(aCatcher);
			return myListeners[myListeners.size() - 1];
		}

		static void TriggerEvent(TEventType &aEvent)
		{
			for (int i = 0; i < static_cast<int>(myListeners.size()); i++)
			{
				if (myListeners[i].HasStoppedListening() == false)
				{
					myListeners[i].Invoke(aEvent);

					if (aEvent.IsInterrupted() == true)
					{
						break;
					}
				}
				else
				{
					myListeners.erase(myListeners.begin() + i);
					i--;
				}
			}
		}

	private:
		static std::vector <EventListener<TEventType>> myListeners;

		EventCollection()
		{
		}
	};

	template <typename TEventType>
	std::vector<EventListener<TEventType>> EventCollection<TEventType>::myListeners;
}
