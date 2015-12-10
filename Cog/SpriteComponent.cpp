#include "SpriteComponent.h"
#include "GameObject.h"
#include "DrawEvent.h"
#include "RenderTarget.h"
#include "Engine.h"
#include "RendererModule.h"
#include "Texture.h"

namespace Cog
{
	SpriteComponent::SpriteComponent(IGameObject &aGameObject, const char *aFileName)
		: GameObjectComponent(aGameObject)
	{
		aGameObject.RegisterEvent(&SpriteComponent::EndUpdate, this);
		aGameObject.RegisterEvent(&SpriteComponent::Draw, this);
		myTexture = Cog::Engine::GetRenderer()->LoadTexture(aFileName);
	}

	void SpriteComponent::EndUpdate(EndUpdateEvent &aEvent)
	{
		previousPosition = currentPosition;
		currentPosition = myObject->GetPosition() - Vector2f(myTexture->GetSize()) / 2.f;
	}

	void SpriteComponent::Draw(DrawEvent &aEvent)
	{
		// aEvent.GetRenderTarget().Render(myTexture, myObject->GetPosition() - Cog::Vector2f(myTexture->GetSize()) / 2.f);
		
		RenderCommand command;
		command.texture = myTexture;
		command.previousPosition = previousPosition;
		command.currentPosition = currentPosition;
		Cog::Engine::ScheduleRendering(command);
	}

	SpriteComponent::~SpriteComponent()
	{
	}
}
