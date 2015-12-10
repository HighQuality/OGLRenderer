#include "Stopwatch.h"

namespace Cog
{
	Stopwatch::Stopwatch()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		myFrequency = frequency.QuadPart;
		Restart();
	}

	void Stopwatch::Restart()
	{
		LARGE_INTEGER startTime;
		QueryPerformanceCounter(&startTime);
		myStartTime = startTime.QuadPart;
	}

	float Stopwatch::GetElapsedSeconds() const
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		return static_cast<float>(static_cast<double>(currentTime.QuadPart - myStartTime) / static_cast<double>(myFrequency));
	}

	Stopwatch::~Stopwatch()
	{
	}
}
