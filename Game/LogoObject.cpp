#include "LogoObject.h"
#include <Engine.h>
#include <UpdateEvent.h>
#include <DrawEvent.h>
#include <EventHost.h>
#include <RendererModule.h>
#include <RenderTarget.h>
#include <ExitingEvent.h>
#include <iostream>
#include <ThreadPool.h>
#include <functional>
#include <WorkItem.h>

LogoObject::LogoObject()
	: mySprite(*this, "../../../Resources/Logo.png")
{
	RegisterEvent<Cog::UpdateEvent>(&LogoObject::Update, this);
	
	myTime = 0.f;
	
	/*RegisterEvent<Cog::ExitingEvent>([=](Cog::ExitingEvent &ev)
	{
		std::cout << "Game will now close" << std::endl;
		// Sets our position to (0,0) because it totally crashes otherwise
		SetPosition(Cog::Vector2f(0.f, 0.f));
	});*/
}

void LogoObject::Update(Cog::UpdateEvent &aEvent)
{
	myTime += aEvent.GetDeltaTime();
	SetPosition(Cog::Vector2f(std::cos(myTime * 3.f) * 200.f, std::sin(myTime * 3.f) * 200.f));
}

LogoObject::~LogoObject()
{
}
