#pragma once
#include <Windows.h>

namespace Cog
{
	class Stopwatch
	{
	public:
		Stopwatch();
		void Restart();
		float GetElapsedSeconds() const;
		~Stopwatch();

	private:
		LONGLONG myFrequency;
		LONGLONG myStartTime;
	};
}
