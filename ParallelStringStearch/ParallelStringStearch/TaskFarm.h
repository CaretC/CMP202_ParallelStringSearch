/*
TaskFarm
========
Task farm to process all the tasks in a farm utilizing the specified number of threads.
*/
#pragma once

// Includes
// ========
#include <queue>
#include <thread>
#include <mutex>
#include <vector>

#include "Task.h"

// Imports
// =======
using std::queue;
using std::thread;
using std::mutex;
using std::unique_lock;
using std::vector;


// Class
// =====
class TaskFarm
{
	// Public
	// ------
	public:
		// Constructor
		TaskFarm();

		// Add a task to the Farm, the task will be deleted once it had been run.
		void Add(Task* task);

		// Run all the tasks in the Farm. 
		void Run();

	// Private
	// -------
	private:
		// Number of threads to use to process the farm. (Default 1)
		unsigned int numberOfThreads = 8;

		// Farm task queue and protection mutex
		queue<Task*> task_queue;
		mutex mutex_task_queue;
};

