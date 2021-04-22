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
#include "StringSearcher.h"

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
	//string textFile = "smallTestText.txt";
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
	cout << endl;
	// ---------------------------------------

	// Main Code
	// ---------
	int numberOfPatterns = patternList.size();


	// TODO: Store all of the results for each pattern search. Maybe in a vector<vector<int>>
	// TODO: Include signaling between threads (e.g. conditional variable or semaphor etc.) maybe use this to process the results or something.....
	
	// TODO: Replace all of the searches with the StringSearcher equivalent
	// +++++++++++++++++
	// String Searcher
	// +++++++++++++++++
	StringSearcher Searcher(&loadedTxt, &patternList, &ui);

	// +++++++++++++++++
	// Sequential Search
	// +++++++++++++++++
	vector<int> sequentialResults;

	BenchmarkTimer timerSeq;
	timerSeq.Start();

	sequentialResults = Searcher.SearchSequential();

	timerSeq.Stop();
	ui.PrintSearchTiming("Sequential CPU Search", timerSeq.Duration());

	ui.PrintResults("Sequential CPU Search", &sequentialResults, &patternList);


	// +++++++++++++++++++++++++++++++++++++++
	// Parallel Search (Basic Implementation)
	// +++++++++++++++++++++++++++++++++++++++
	vector<int> simpParallelResults;

	BenchmarkTimer timerPar;
	timerPar.Start();

	simpParallelResults = Searcher.SearchParallelSimple(numberOfPatterns);

	timerPar.Stop();
	ui.PrintSearchTiming("Parallel CPU Search (Basic)", timerPar.Duration());

	ui.PrintResults("Parallel CPU Search (Basic)", &simpParallelResults, &patternList);

	// +++++++++++++++++++++++++++++++++
	// Parallel Search (Farmer & Worker)
	// +++++++++++++++++++++++++++++++++
	vector<int> taskParallelResults;

	BenchmarkTimer farmTimer;
	farmTimer.Start();

	taskParallelResults = Searcher.SearchParallelTasks(numberOfPatterns);

	farmTimer.Stop();
	ui.PrintSearchTiming("Parallel CPU Search (Farm & Worker)", farmTimer.Duration());

	ui.PrintResults("Parallel CPU Search (Farm & Worker)", &taskParallelResults, &patternList);
}
// ============================================================================================================================