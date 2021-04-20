/*
TaskFarm
========
Task farm to process all the tasks in a farm utilizing the specified number of threads.
*/

// Includes
// ========
#include "TaskFarm.h"

// Constructor
// ===========
TaskFarm::TaskFarm()
{
}

// Public Functions
// ================
// Add a task to the Farm, the task will be deleted once it had been run.
void TaskFarm::Add(Task* task)
{
	unique_lock<mutex> lock(mutex_task_queue);
	task_queue.push(task);
}

// Run all the tasks in the Farm. 
void TaskFarm::Run()
{
	// Vector to store the worker threads
	vector<thread*> worker_threads;

	// Lambda definition of the thread_worker
	auto thread_worker = [&]() -> int {
		// Infinite Loop
		while (true)
		{
			// Lock Task Queue
			mutex_task_queue.lock();

			// If the queue is not empty run a task from the queue and remove it
			if (!task_queue.empty())
			{
				// Get the pointer of the taskToRun
				Task* taskToRun = task_queue.front();

				// Pop this task from the queue
				task_queue.pop();

				// Unlock task queue
				mutex_task_queue.unlock();

				taskToRun->Run();
			}
			else
			{
				mutex_task_queue.unlock();
				return 0;
			}
		}
	};

	// Start the required number of worker threads
	for (int i = 0; i < numberOfThreads; i++)
	{
		worker_threads.push_back(new thread(thread_worker));
	}

	// Join all the worker threads to synchronize
	for (int i = 0; i < numberOfThreads; i++)
	{
		worker_threads[i]->join();
	}

	// Clean up memory
	for (int i = 0; i < numberOfThreads; i++)
	{
		delete worker_threads[i];
	}
}
