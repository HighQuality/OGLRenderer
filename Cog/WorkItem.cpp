#include "WorkItem.h"

namespace Cog
{
	WorkItem::WorkItem(std::function<void()> *aWork)
	{
		mySignal = new AwaitableSignal();
		myWork = aWork;
	}

	void WorkItem::DoWork()
	{
		(*myWork)();
		mySignal->SignalOne();
	}

	void WorkItem::Wait()
	{

	}

	WorkItem::~WorkItem()
	{
	}
}
