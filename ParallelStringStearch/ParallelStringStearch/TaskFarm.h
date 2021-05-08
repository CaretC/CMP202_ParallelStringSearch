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

// Test
#include <unordered_map>
#include <string>

#include "Task.h"
#include "SearchTask.h"

// Imports
// =======
using std::queue;
using std::thread;
using std::mutex;
using std::unique_lock;
using std::vector;

// Test
using std::unordered_map;
using std::string;

// Class
// =====
class TaskFarm
{
	// Public
	// ------
	public:
		// Constructor
		TaskFarm(int threads);

		// Add a task to the Farm, the task will be deleted once it had been run.
		void Add(SearchTask* task);

		// Run all the tasks in the Farm. 
		void Run(unordered_map<string, int>* outResults);

	// Private
	// -------
	private:
		// Number of threads to use to process the farm. (Default 1)
		unsigned int numberOfThreads = 1;

		// Farm task queue and protection mutex
		queue<SearchTask*> task_queue;
		mutex mutex_task_queue;
		mutex mutex_result;
};

