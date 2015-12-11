#pragma once
#include "GameObjectComponent.h"
#include "Vector.h"

namespace Cog
{
	class EndUpdateEvent;
	class DrawEvent;
	class Texture;
	class SpriteComponent : public GameObjectComponent
	{
	public:
		SpriteComponent(IGameObject &aGameObject, const char *aFileName);
		~SpriteComponent();

	private:
		void EndUpdate(EndUpdateEvent &aEvent);
		void Draw(DrawEvent &aEvent);
		Vector2f previousPosition,
			currentPosition;
		Texture *myTexture;
	};
}
