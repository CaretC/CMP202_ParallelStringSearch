/*
CMP 202 Coursework - Parallel String Search
*/

// Includes
// ========
#include <iostream>
#include <thread>
#include <string>

#include "ConsoleUI.h"
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
	// Console UI
	// ----------
	ConsoleUI ui;

	// Welcome Screen
	// --------------
	ui.PrintWelcome();
	ui.WaitForKeyPress();
	ui.Clear();

	// Load text
	// ----------
	string textFile = "testText.txt";
	ui.PrintFileLoadingMessage(textFile);
	
	TextLoader tl;
	string loadedTxt;
	tl.LoadFile(textFile, loadedTxt);

	ui.PrintFileLoadMessage(textFile);
	// ---------------------------------

	// Load Pattern List
	// -----------------
	string patternFile = "textPatterns.txt";
	ui.PrintFileLoadingMessage(patternFile);

	vector<string> patternList;
	PatternListLoader PattLoader;
	PattLoader.LoadPatternList("textPatterns.txt", patternList);
	
	ui.PrintFileLoadMessage(patternFile);
	// ---------------------------------------

	// Main Code
	// ---------
	int numberOfPatterns = patternList.size();

	// +++++++++++++++++
	// Sequential Search
	// +++++++++++++++++
	//cout << "Staring sequential search..." << endl;
	ui.PrintSearchStartMessage("Sequential Search");

	BenchmarkTimer timerSeq;
	timerSeq.Start();

	for (int i = 0; i < numberOfPatterns; i++)
	{
		SearchTask search(patternList[i], &loadedTxt);
		search.Run();
	}

	timerSeq.Stop();

	ui.PrintSearchCompleteMessage("Sequential CPU Search");
	ui.PrintSearchTiming("Sequential CPU Search", timerSeq.Duration());


	// +++++++++++++++++++++++++++++++++++++++
	// Parallel Search (Basic Implementation)
	// +++++++++++++++++++++++++++++++++++++++
	ui.PrintSearchStartMessage("Parallel CPU Search (Basic)");

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

	ui.PrintSearchCompleteMessage("Parallel CPU Search (Basic)");
	ui.PrintSearchTiming("Parallel CPU Search (Basic)", timerPar.Duration());


	// +++++++++++++++++++++++++++++++++
	// Parallel Search (Farmer & Worker)
	// +++++++++++++++++++++++++++++++++
	ui.PrintSearchStartMessage("Parallel CPU Search (Farm & Worker)");

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

	ui.PrintSearchCompleteMessage("Parallel CPU Search (Farm & Worker)");
	ui.PrintSearchTiming("Parallel CPU Search (Farm & Worker)", farmTimer.Duration());
}
// ============================================================================================================================