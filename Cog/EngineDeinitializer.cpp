#include "EngineDeinitializer.h"
#include "Engine.h"

namespace Cog
{
	EngineDeinitializer::EngineDeinitializer()
	{
	}

	EngineDeinitializer::~EngineDeinitializer()
	{
		Engine::Destruct();
	}
}
