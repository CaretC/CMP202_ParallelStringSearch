/*
Search Task
===========
A single string search task to be processed by the farm over multiple threads. Inherits from Task Class.
*/
#pragma once

// Includes
// ========
#include <string>
#include <vector>
#include <mutex>

#include "Task.h";
#include "CharTable.h"

// Imports
// =======
using std::string;
using std::vector;
using std::mutex;

// Class
// =====
class SearchTask : public Task
{
	// Public
	// ------
	public:
		// Constructor
		SearchTask(string pattern, string* text);

		// Run this SearchTask
		int Run();

		// Run this SearchTask, for used when it is required to run in parallel and still capture the result
		void RunParallel(vector<int>* outResults);

		// Reutrns the Seach Task pattern
		string GetPattern();

	// Private
	// -------
	private:
		string pattern;
		string* p_text;

		// Boyer Moore Horspool Search
		int BMHSearch(string pattern, string* text);
};

