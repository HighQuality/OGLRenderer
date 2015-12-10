#pragma once
#include <functional>
#include "AwaitableSignal.h"

namespace Cog
{
	class WorkItem
	{
	public:
		WorkItem(std::function<void()> *aWork);
		~WorkItem();

		void Wait();
		void DoWork();

	private:
		AwaitableSignal *mySignal;
		std::function<void()> *myWork;
	};
}
