#pragma once
#include "Event.h"

namespace Cog
{
	class CloseButtonPressedEvent : public Event
	{
	public:
		CloseButtonPressedEvent();
		~CloseButtonPressedEvent();
	};
}
