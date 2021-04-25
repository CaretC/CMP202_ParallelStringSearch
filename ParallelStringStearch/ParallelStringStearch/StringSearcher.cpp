/*
StringSearcher
==============
Searches for a pattern or vector of patterns within a given text. String searcher can be used in several different
methods. Sequential, parallel basic and parallel farm. It can also out put the number of pattern occurances in the
text and the positions of these occurances.
*/

// Includes
// ========
#include "StringSearcher.h"

// Constructor
// ===========
// Constructor patten list
StringSearcher::StringSearcher(string* searchText, vector<string>* patternList, ConsoleUI* ui)
{
	pSearchText = searchText;
	pPatternList = patternList;
	pUi = ui;
}

// Public Functions
// ================
// Conduct a sequential string search
vector<int> StringSearcher::SearchSequential()
{
	string searchName = "Sequential Search";

	pUi->PrintSearchStartMessage(searchName);

	int numberOfPatterns = pPatternList->size();
	vector<int> results;

	for (int i = 0; i < numberOfPatterns; i++)
	{		
		SearchTask search((*pPatternList)[i], pSearchText);
		int patternMatches = search.Run();
		results.push_back(patternMatches);
	}

	pUi->PrintSearchCompleteMessage(searchName);

	return results;
}

// Conduct a sequential string search and save the positions to an output vector
int StringSearcher::SearchSequential(vector<int>* positionsOutput)
{
	// TODO: Implement SearchSequential(vector<int>* positionsOutput)
	return 0;
}

// Conduct a simple parallel search
vector<int> StringSearcher::SearchParallelSimple(int searchThreads)
{
	string searchName = "Parallel CPU Search (Basic)";
	pUi->PrintSearchStartMessage(searchName);

	vector<int> results;

	// Define the number of threads to use
	const unsigned int numThreads = searchThreads;

	// Store the threads
	vector<thread> threads;

	// Store SearchTasks
	vector<SearchTask> searches;

	// Make Tasks
	for (int i = 0; i < numThreads; i++)
	{
		searches.push_back(SearchTask((*pPatternList)[i], pSearchText));
	}

	// Populate the threads
	for (int i = 0; i < numThreads; i++)
	{
		threads.push_back(thread(&SearchTask::RunParallel, searches[i], &results));
	}

	// Join all of the threads
	for (int i = 0; i < numThreads; i++)
	{
		threads[i].join();
	}

	pUi->PrintSearchCompleteMessage(searchName);

	return results;
}

// Conduct a simple parallel search and save the positons to a output vector
int StringSearcher::SearchParallelSimple(vector<int>* positionsOutput)
{
	// TODO: Implement SearchParallelSimple(vector<int>* positionsOutput)
	return 0;
}

// Conduct a task based parallel search
vector<int> StringSearcher::SearchParallelTasks(int searchThreads)
{
	pUi->PrintSearchStartMessage("Parallel CPU Search (Farm & Worker)");

	vector<int> results;

	TaskFarm farm(searchThreads);

	// Add a task for each of the patterns to be searched for
	for (int i = 0; i < pPatternList->size(); i++)
	{
		farm.Add(new SearchTask((*pPatternList)[i], pSearchText));
	}

	// Run all the farm tasks
	farm.Run(&results);

	pUi->PrintSearchCompleteMessage("Parallel CPU Search (Farm & Worker)");

	return results;
}

// Conduct a task based parallel search and save the positions to an output vector
int StringSearcher::SearchParallelTasks(vector<int>* positonsOuput)
{
	// TODO: Implement SearchParallelTasks(vector<int>* positonsOuput)
	return 0;
}

// Get the PatternList assosciated with this StringSearcher instance
vector<string>* StringSearcher::GetPatternList()
{
	return pPatternList;
}

// Private Functions
// =================


