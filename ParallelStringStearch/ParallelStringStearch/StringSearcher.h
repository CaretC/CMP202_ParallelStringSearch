/*
StringSearcher
==============
Searches for a pattern or vector of patterns within a given text. String searcher can be used in several different
methods. Sequential, parallel basic and parallel farm. It can also out put the number of pattern occurances in the 
text and the positions of these occurances.
*/
#pragma once

// Includes
// ========
#include <string>
#include <vector>
#include <thread>

#include "SearchTask.h"
#include "ConsoleUI.h"
#include "TaskFarm.h"

// Imports
// =======
using std::string;
using std::vector;
using std::thread;

// Class
// =====
class StringSearcher
{
	// Public
	// ------
	public:
		// Constructor patten list
		StringSearcher(string* searchText, vector<string>* patternList, ConsoleUI* ui);

		// Conduct a sequential string search
		vector<int> SearchSequential();

		// Conduct a sequential string search and save the positions to an output vector
		int SearchSequential(vector<int>* positionsOutput);

		// Conduct a simple parallel search
		vector<int> SearchParallelSimple(int searchThreads);

		// Conduct a simple parallel search and save the positons to a output vector
		int SearchParallelSimple(vector<int>* positionsOutput);

		// Conduct a task based parallel search
		vector<int> SearchParallelTasks(int searchThreads);

		// Conduct a task based parallel search and save the positions to an output vector
		int SearchParallelTasks(vector<int>* positonsOuput);

		// Get the PatternList pointer assosciated with this StringSearcher instance
		vector<string>* GetPatternList();

	// Private
	// -------
	private:
		// Store a pointer to the search text
		string* pSearchText;

		// Store a pointer to the vector containing the pattern list
		vector<string>* pPatternList;

		// Store a pointer to the console UI
		ConsoleUI* pUi;

		// Store single pattern
		string singlePattern;
};

