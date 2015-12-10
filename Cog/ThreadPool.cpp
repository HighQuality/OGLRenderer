#include "ThreadPool.h"
#include "WorkItem.h"

namespace Cog
{
	ThreadPool::ThreadPool(int aNumberOfWorkers)
	{
		myIsStopping = false;

		for (int i = 0; i < aNumberOfWorkers; i++)
		{
			myWorkers.push_back(new std::thread(&ThreadPool::WorkerThread, this, i + 1));
		}
	}

	ThreadPool::~ThreadPool()
	{
		myIsStopping = true;
		// Notify all threads to wake up
		myConditional.notify_all();
		for (int i = 0; i < myWorkers.size(); i++)
		{
			myWorkers[i]->join();
			delete myWorkers[i];
		}
		myWorkers.clear();
	}

	std::shared_ptr<WorkItem> ThreadPool::QueueWorkItem(std::function<void()> &aWorkItem)
	{
		std::shared_ptr<WorkItem> someWork = std::make_shared<WorkItem>(new std::function<void()>(aWorkItem));
		myWork.push_back(someWork);
		myConditional.notify_one();
		return someWork;
	}

	void ThreadPool::WorkerThread(int workerId)
	{
		for (;;)
		{
			std::unique_lock<std::mutex> lock(myMutex);
			// Wait for a signal of new work
			myConditional.wait(lock);

			// Stop this worker thread
			if (myIsStopping == true)
			{
				lock.unlock();
				break;
			}

			while (myWork.size() > 0)
			{
				// Do the first work in the queue
				std::shared_ptr<WorkItem> currentWork = myWork[0];
				myWork.erase(myWork.begin());
				// Let another worker take a job
				lock.unlock();

				currentWork->DoWork();

				// Re-acquire the lock to check for more work
				lock.lock();
			}

			// We woke up for no reason (happens supriously)
			lock.unlock();
		}
	}
}
