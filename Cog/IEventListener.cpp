#include "IEventListener.h"

namespace Cog
{
	IEventListener::IEventListener()
	{
		myHasStoppedListening = false;
	}

	bool IEventListener::HasStoppedListening() const
	{
		return myHasStoppedListening;
	}

	void IEventListener::StopListen()
	{
		myHasStoppedListening = true;
	}

	IEventListener::~IEventListener()
	{
	}
}
