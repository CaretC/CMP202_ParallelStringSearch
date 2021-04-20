/*
Search Task
===========
A single string search task to be processed by the farm over multiple threads. Inherits from Task Class.
*/
#pragma once

// Includes
// ========
#include <string>

#include "Task.h";
#include "CharTable.h"

// Imports
// =======
using std::string;

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
		void Run();

	// Private
	// -------
	private:
		string pattern;
		string* p_text;

		// Boyer Moore Horspool Search
		int BMHSearch(string pattern, string* text);
};

