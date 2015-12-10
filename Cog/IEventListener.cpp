#include "IEventListener.h"

IEventListener::IEventListener()
{
	myHasStoppedListening = false;
}

bool IEventListener::HasStoppedListening() const
{
	return myHasStoppedListening;
}

IEventListener::~IEventListener()
{
}
