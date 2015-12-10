#pragma once
#include "Event.h"

namespace Cog
{
	class UpdateEvent : public Event
	{
	public:
		UpdateEvent(float aDeltaTime);
		~UpdateEvent();

		inline float GetDeltaTime();

	private:
		float myDeltaTime;
	};

	float UpdateEvent::GetDeltaTime()
	{
		return myDeltaTime;
	}
}
