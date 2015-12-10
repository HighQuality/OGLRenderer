#include "UpdateEvent.h"

namespace Cog
{
	UpdateEvent::UpdateEvent(float aDeltaTime)
	{
		myDeltaTime = aDeltaTime;
	}

	UpdateEvent::~UpdateEvent()
	{
	}
}
