#pragma once
#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <memory>

namespace Cog
{
	class WorkItem;
	class AwaitableSignal;
	class ThreadPool
	{
	public:
		ThreadPool();
		std::shared_ptr<WorkItem> QueueWorkItem(std::function<void()> &aWorkItem);
		~ThreadPool();

	private:
		std::vector<std::thread*> myWorkers;
		std::vector<std::shared_ptr<WorkItem>> myWork;
		std::mutex myMutex;
		std::condition_variable myConditional;
		volatile bool myIsStopping;

		void WorkerThread(int workerId);
	};
}
