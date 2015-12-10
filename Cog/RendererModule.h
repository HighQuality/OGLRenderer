#pragma once
#include "Color.h"

namespace Cog
{
	class Window;
	class RenderTarget;
	class Texture;

	class RendererModule
	{
	public:
		virtual ~RendererModule();

		virtual Window *CreateHiddenWindowAndContext() = 0;
		virtual Window *GetWindow() = 0;

		virtual void TriggerEvents() = 0;
		virtual void Clear() = 0;
		virtual void PresentBackBuffer() = 0;

		virtual RenderTarget *GetRenderTarget() = 0;

		virtual Texture *LoadTexture(const char *aFileName) = 0;

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