#pragma once
#include <GameObject.h>
#include <SpriteComponent.h>

namespace Cog
{
	class UpdateEvent;
	class DrawEvent;
	class Texture;
}
class MainScene;

class LogoObject : public Cog::GameObject<MainScene>
{
public:
	LogoObject();
	~LogoObject();

	void Update(Cog::UpdateEvent &aEvent);

private:
	Cog::SpriteComponent mySprite;
	float myTime;
};
