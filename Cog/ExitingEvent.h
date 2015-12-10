#pragma once
#include "Event.h"

namespace Cog
{
	class ExitingEvent : public Event
	{
	public:
		ExitingEvent();
		~ExitingEvent();
	};
}
