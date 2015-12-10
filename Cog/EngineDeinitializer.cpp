#include "EngineDeinitializer.h"
#include "Engine.h"
#include <assert.h>

namespace Cog
{
	EngineDeinitializer::EngineDeinitializer()
	{
	}

	EngineDeinitializer::~EngineDeinitializer()
	{
		assert(Engine::IsInitialized() == false);
	}
}
