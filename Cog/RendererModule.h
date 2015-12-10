#pragma once
#include "Color.h"

namespace Cog
{
	class Window;
	
	class RendererModule
	{
	public:
		virtual ~RendererModule();

		virtual Window *CreateHiddenWindowAndContext() = 0;
		virtual Window *GetWindow() = 0;

		virtual void TriggerEvents() = 0;
		virtual void Clear() = 0;
		virtual void PresentBackBuffer() = 0;

		void SetBackgroundColor(const Color &aColor);
		inline Color GetBackgroundColor() const;

	protected:
		RendererModule();

	private:
		Color myBackgroundColor;
	};

	Color RendererModule::GetBackgroundColor() const
	{
		return myBackgroundColor;
	}
}