#pragma once
#include "IEventListener.h"

template<typename TEventType>
class EventListener : public IEventListener
{
public:
	EventListener()
	{
	}
	~EventListener()
	{
	}

	template <typename TEventCatcher>
	void SetCatcher(TEventCatcher aEventCatcher)
	{
		myEventCatcher = aEventCatcher;
	}

	void Invoke(TEventType &aEvent) const
	{
		myEventCatcher(aEvent);
	}

private:
	std::function<void(TEventType&)> myEventCatcher;
};

