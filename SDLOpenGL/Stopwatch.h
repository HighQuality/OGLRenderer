#include <Windows.h>

class Stopwatch
{
public:
	Stopwatch();
	void Restart();
	double GetElapsedSeconds() const;
	~Stopwatch();

private:
	__int64 myCounterStart;
	double myPCFreq;
};
