#pragma once
#include "GameObject.h"

namespace Cog
{
	class CameraObject : public GameObject<GameScene>
	{
	public:
		CameraObject();
		~CameraObject();
	};
}
