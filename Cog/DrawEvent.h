#pragma once
#include "Event.h"

namespace Cog
{
	class RenderTarget;
	class DrawEvent : public Event
	{
	public:
		DrawEvent(/*RenderTarget &aRenderTarget*/);
		~DrawEvent();

		//inline RenderTarget &GetRenderTarget() const;

	private:
		//RenderTarget *myRenderTarget;
	};

	/*RenderTarget &DrawEvent::GetRenderTarget() const
	{
		return *myRenderTarget;
	}*/
}
