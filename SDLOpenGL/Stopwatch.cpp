#include "stdafx.h"
#include "Stopwatch.h"
#include <iostream>

Stopwatch::Stopwatch()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!" << std::endl;
	myPCFreq = static_cast<double>(li.QuadPart);
	Restart();
}

double Stopwatch::GetElapsedSeconds() const
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return static_cast<double>(li.QuadPart - myCounterStart) / myPCFreq;
}

void Stopwatch::Restart()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	myCounterStart = li.QuadPart;
}

Stopwatch::~Stopwatch()
{
}
