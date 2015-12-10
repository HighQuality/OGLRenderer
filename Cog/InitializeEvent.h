#pragma once
#include "Event.h"

namespace Cog
{
	class InitializeEvent : public Event
	{
	public:
		InitializeEvent();
		~InitializeEvent();
	};
}
