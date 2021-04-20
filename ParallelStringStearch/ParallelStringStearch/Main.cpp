/*
CMP 202 Coursework - Parallel String Search
*/

// Includes
// ========
#include <iostream>
#include <thread>
#include <string>

#include "BenchmarkTimer.h"
#include "CsvWriter.h"
#include "TextLoader.h"
#include "PatternListLoader.h"
#include "CharTable.h"
#include "TaskFarm.h"
#include "SearchTask.h"

// Imports
// =======
using std::cout;
using std::endl;
using std::thread;
using std::string;

// Main
// ====
int main() {
	// Load text
	// ----------
	string textFile = "testText.txt";
	cout << "Loading " << textFile << "..." << endl;
	
	TextLoader tl;
	string loadedTxt;

	tl.LoadFile(textFile, loadedTxt);

	cout << textFile << " loaded" << endl;
	// ---------------------------------

	// Load Pattern List
	// -----------------
	cout << "Load textPatterns.txt..." << endl;

	vector<string> patternList;

	PatternListLoader PattLoader;
	PattLoader.LoadPatternList("textPatterns.txt", patternList);
	
	cout << "textPatterns.txt loaded" << endl;
	// ---------------------------------------

	// Main Code
	// ---------
	int numberOfPatterns = patternList.size();

	// +++++++++++++++++
	// Sequential Search
	// +++++++++++++++++
	cout << "Staring sequential search..." << endl;

	BenchmarkTimer timerSeq;
	timerSeq.Start();

	for (int i = 0; i < numberOfPatterns; i++)
	{
		SearchTask search(patternList[i], &loadedTxt);
		search.Run();
	}

	timerSeq.Stop();

	cout << "Sequential search completed in " << timerSeq.Duration() << "ms" << endl;


	// +++++++++++++++++++++++++++++++++++++++
	// Parallel Search (Basic Implementation)
	// +++++++++++++++++++++++++++++++++++++++
	cout << "Starting parallel search (basic)..." << endl;

	BenchmarkTimer timerPar;
	timerPar.Start();

	// Define the number of threads to use
	const unsigned int numThreads = patternList.size();

	// Store the threads
	vector<thread> threads;

	// Store SearchTasks
	vector<SearchTask> searches;

	// Make Tasks
	for (int i = 0; i < numThreads; i++)
	{
		searches.push_back(SearchTask(patternList[i], &loadedTxt));
	}
	// Populate the threads
	for (int i = 0; i < numThreads; i++)
	{
		threads.push_back(thread(&SearchTask::Run, searches[i]));
	}

	// Join all of the threads
	for (int i = 0; i < numThreads; i++)
	{
		threads[i].join();
	}

	timerPar.Stop();

	// Done
	cout << "All threads done!" << endl;
	cout << "Parallel search (basic) complete!" << "Search took " << timerPar.Duration() << "ms" << endl;

	// +++++++++++++++++++++++++++++++++
	// Parallel Search (Farmer & Worker)
	// +++++++++++++++++++++++++++++++++
	cout << "Starting parallel search (Farm & Worker)..." << endl;

	BenchmarkTimer farmTimer;
	farmTimer.Start();

	TaskFarm farm;

	// Add a task for each of the patterns to be searched for
	for (int i = 0; i < patternList.size(); i++)
	{
		farm.Add(new SearchTask(patternList[i], &loadedTxt));
	}

	// Run all the farm tasks
	farm.Run();

	farmTimer.Stop();

	cout << "Farm Processing Compete!" << endl;
	cout << "Parallel search (Farm & Worker) complete!" << "Search took " << farmTimer.Duration() << "ms" << endl;
}
// ============================================================================================================================