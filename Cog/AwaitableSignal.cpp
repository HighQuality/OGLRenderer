#include "AwaitableSignal.h"


AwaitableSignal::AwaitableSignal()
{
	mySignal = false;
}

void AwaitableSignal::Wait()
{
	myMutex.lock();
	if (mySignal == true)
	{
		myMutex.unlock();
		return;
	}
	myMutex.unlock();

	std::unique_lock<std::mutex> lock(myMutex);
	// Wait until mySignal turns into true and then reset it to false
	myConditionVariable.wait(lock, [=]{ return mySignal; });
	mySignal = false;
	lock.unlock();
}

void AwaitableSignal::SignalOne()
{
	myMutex.lock();
	if (mySignal == true)
	{
		myMutex.unlock();
		return;
	}
	mySignal = true;
	myMutex.unlock();
	myConditionVariable.notify_one();
}

AwaitableSignal::~AwaitableSignal()
{
}
