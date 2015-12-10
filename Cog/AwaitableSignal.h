#pragma once
#include <condition_variable>
#include <mutex>

class AwaitableSignal
{
public:
	AwaitableSignal();
	~AwaitableSignal();

	void Wait();
	void SignalOne();

private:
	volatile bool mySignal;
	std::mutex myMutex;
	std::condition_variable myConditionVariable;
};

