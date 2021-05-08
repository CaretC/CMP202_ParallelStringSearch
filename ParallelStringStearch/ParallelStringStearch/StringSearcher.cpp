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
	// Old
	//this is broken fix it
	//string searchName = "Parallel CPU Search (Basic)";
	//pUi->PrintSearchStartMessage(searchName);

	/*vector<int> results;
	mutex mutex_resutls;*/

	//// Define the number of threads to use
	//const unsigned int numThreads = searchThreads;

	//// Store the threads
	//vector<thread*> threads;

	//// Store SearchTasks
	//vector<SearchTask> searches;

	//// New Implementation
	//// ++++++++++++++++++++++++++++++
	//int pos = 0;

	////Make Tasks
	//for (int i = 0; i < pPatternList->size(); i++)
	//{
	//	searches.push_back(SearchTask((*pPatternList)[i], pSearchText));
	//}

	//// Process tasks over threads
	//while (pos < pPatternList->size())
	//{
	//	// Populate threads
	//	int threadsCreated = 0;
	//	for (int i = 0; i < searchThreads; i++)
	//	{
	//		if ((i + pos) < pPatternList->size())
	//		{
	//			threads.push_back(new thread(&SearchTask::RunParallel, searches[i + pos], &results, &mutex_resutls));
	//			threadsCreated++;
	//		}
	//	}

	//	// Join threads
	//	for (int i = 0; i < threadsCreated; i++)
	//	{
	//		threads[i]->join();
	//	}

	//	//HACK: Check through this!
	//	// Clean up memory
	//	for (int i = 0; i < threads.size(); i++)
	//	{
	//		delete threads[i];
	//	}

	//	// Clear up
	//	threads.clear();

	//	pos += threadsCreated;
	//	threadsCreated = 0;
	//}

	//pUi->PrintSearchCompleteMessage(searchName);
	// new
	string searchName = "Parallel CPU Search (Basic)";
	pUi->PrintSearchStartMessage(searchName);

	vector<int> results;	
	queue<SearchTask*> searches;
	int pos = 0;

	// Populate search queue
	for (auto pattern : (*pPatternList))
	{
		searches.push(new SearchTask(pattern, pSearchText));
	}

	// While there is still searches in the queue
	while(!searches.empty())
	{
		vector<thread*> threads;

		// Make searchThreads number of threads
		for (int th = 0; th < searchThreads; th++)
		{
			if ((searches.size() - th) > 0)
			{
				pUi->PrintMessage("Making thread " + th);
				// Run seach task from queue
				threads.push_back(new thread(&SearchTask::RunParallel, searches.front(), &results));
			}
		}

		// Wait for all the running threads to finish
		for (auto th : threads)
		{
			pUi->PrintMessage("Joining thread ");
			th->join();
		}

		// Clean up threads
		for (auto th : threads)
		{
			if (!searches.empty())
			{
				// Clean up search task from the heap
				delete searches.front();
				// Pop the last saerch from the queue
				searches.pop();
			}

			delete th;
		}

		//delete[] &threads;

		// Clear the thread vector
		//threads.clear();
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
//vector<int> StringSearcher::SearchParallelTasks(int searchThreads)
unordered_map<string, int> StringSearcher::SearchParallelTasks(int searchThreads)
{
	pUi->PrintSearchStartMessage("Parallel CPU Search (Farm & Worker)");

	//vector<int> results;
	unordered_map <string, int> results;

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


