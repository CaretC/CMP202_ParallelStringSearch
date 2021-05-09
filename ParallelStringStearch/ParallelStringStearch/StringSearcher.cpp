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

// Conduct a task based parallel search
unordered_map<string, int> StringSearcher::SearchParallelTasks(int searchThreads)
{
	pUi->PrintSearchStartMessage("Parallel CPU Search (Farm & Worker)");

	unordered_map <string, int> results;

	// Make Channel to handle data writing
	Channel dataChan(&results);
	dataChan.Open();

	// Make the Channel writer thread
	thread writerThread([&] {
	while (dataChan.IsOpen())
	{
		pair<string, int> res;
		dataChan.read(&res);
		results[res.first] = res.second;
	}
	});

	// Make the search task farm
	TaskFarm farm(searchThreads);

	// Add a task for each of the patterns to be searched for
	for (int i = 0; i < pPatternList->size(); i++)
	{
		farm.Add(new SearchTask((*pPatternList)[i], pSearchText));
	}

	// Run all the farm tasks
	farm.Run(&dataChan);

	// Close the data channel and join writer thread to the main
	dataChan.Close();
	writerThread.join(); // Could a barrier be used here

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


