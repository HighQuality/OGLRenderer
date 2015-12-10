#include "Event.h"

namespace Cog
{
	Event::Event()
	{
		myIsInterrupted = false;
	}

	void Event::Interrup()
	{
		myIsInterrupted = true;
	}

	Event::~Event()
	{
	}
}
