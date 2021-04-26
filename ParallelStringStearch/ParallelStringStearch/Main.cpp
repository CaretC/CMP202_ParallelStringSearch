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

// Function Prototypes
// ===================
void PrintWelcomeScreen(ConsoleUI* ui);
string LoadSearchTextFile(ConsoleUI* ui, string filePath);
vector<string> LoadPatternListFile(ConsoleUI* ui, string filePath);
vector<int> SequentialSearch(ConsoleUI* ui, StringSearcher* searcher, long long* outTiming);
vector<int> ParallelSearchBasic(ConsoleUI* ui, StringSearcher* searcher, int threadQuantity, vector<long long>* outTiming);
vector<int> ParallelSearchTasks(ConsoleUI* ui, StringSearcher* searcher, int threadQuantity, vector<long long>* outTiming);

// TODO: Store all of the results for each pattern search. Maybe in a vector<vector<int>>
// TODO: Include signaling between threads (e.g. conditional variable or semaphor etc.) maybe use this to process the results or something.....
// FIX: Search results thread safety in parallel searcher, something is wrong here.
// FIX: The way the number of threads works in the StringSearcher... something is not working it seems to need the values to match the pattern list length

// Main
// ====
int main() {
	// Instances
	// ----------
	ConsoleUI ui;
	string searchText;
	CsvWriter cw;
	vector<string> patternList;
	StringSearcher Searcher(&searchText, &patternList, &ui);

	// Thread Timings
	long long timingSeq = 0;
	vector<long long> timingSimp;
	vector<long long> timingTask;

	// Pattern Timings
	vector<long long> timingSimpPatt;
	vector<long long> timingTaskPatt;

	// Welcome Screen
	// --------------
	PrintWelcomeScreen(&ui);

	// Load text
	// ----------
	searchText = LoadSearchTextFile(&ui, "testText.txt");

	// Load Pattern List
	// -----------------
	patternList = LoadPatternListFile(&ui, "textPatterns.txt");

	// Main Code
	// ---------
	int numberOfPatterns = patternList.size();

	// Sequential Search
	// -----------------
	vector<int> sequentialResults = SequentialSearch(&ui, &Searcher, &timingSeq);

	// Vary Thread Number
	// -------------------
	for (int threads = 1; threads <= 20; threads++)
	{
		// Parallel Search (Basic Implementation)
		// --------------------------------------
		vector<int> simpParallelResults = ParallelSearchBasic(&ui, &Searcher, threads, &timingSimp);

		// Parallel Search (Task Based)
		// ----------------------------
		vector<int> taskParallelResults = ParallelSearchTasks(&ui, &Searcher, threads, &timingTask);
	}

	cw.WriteToFile(timingSeq, timingSimp, timingTask, "varyThreadsTiming.csv");

	// Vary Patterns
	// --------------
	for (int patterns = 1; patterns <= 20; patterns++)
	{
		string msg = "Searching for " + patterns;
		ui.PrintMessage(msg);
		vector<string> varyPatt;

		for (int i = 0; i < patterns; i++)
		{
			varyPatt.push_back(patternList[i]);
		}

		StringSearcher pattSearch(&searchText, &varyPatt, &ui);

		vector<int> simpParallelResults = ParallelSearchBasic(&ui, &pattSearch, 8, &timingSimpPatt);
		vector<int> taskParallelResults = ParallelSearchTasks(&ui, &pattSearch, 8, &timingTaskPatt);
	}

	long long x = 0;
	cw.WriteToFile(x, timingSimpPatt, timingTaskPatt, "varyPatternTiming.csv");

	// Vary Text Length
	// ----------------
	// TODO: Implement
}
// ============================================================================================================================

// Functions
// =========
// Print Welcome Screen
void PrintWelcomeScreen(ConsoleUI* ui) 
{
	ui->PrintWelcome();
	ui->WaitForKeyPress();
	ui->Clear();
}

// Load Search Text File
string LoadSearchTextFile(ConsoleUI* ui, string filePath) 
{
	ui->PrintFileLoadingMessage(filePath);

	TextLoader tl;
	string loadedTxt;
	tl.LoadFile(filePath, loadedTxt);

	ui->PrintFileLoadMessage(filePath);
	return loadedTxt;
}

// Load Pattern List File
vector<string> LoadPatternListFile(ConsoleUI* ui, string filePath) 
{
	ui->PrintFileLoadingMessage(filePath);

	vector<string> patternList;
	PatternListLoader PattLoader;
	PattLoader.LoadPatternList(filePath, patternList);

	ui->PrintFileLoadMessage(filePath);
	cout << endl;
	return patternList;
}

// Conduct Sequential Search
vector<int> SequentialSearch(ConsoleUI* ui, StringSearcher* searcher, long long* outTiming)
{
	vector<int> results;

	BenchmarkTimer timerSeq;
	timerSeq.Start();

	results = searcher->SearchSequential();

	timerSeq.Stop();
	ui->PrintSearchTiming("Sequential CPU Search", timerSeq.Duration());
	*outTiming = timerSeq.Duration();

	ui->PrintResults("Sequential CPU Search", &results, searcher->GetPatternList());
	return results;
}

// Conduct Parallel Search (Basic)
vector<int> ParallelSearchBasic(ConsoleUI* ui, StringSearcher* searcher, int threadQuantity, vector<long long>* outTiming)
{
	vector<int> results;

	BenchmarkTimer timerPar;
	timerPar.Start();

	results = searcher->SearchParallelSimple(threadQuantity);

	timerPar.Stop();
	ui->PrintSearchTiming("Parallel CPU Search (Basic)", timerPar.Duration());

	ui->PrintResults("Parallel CPU Search (Basic)", &results, searcher->GetPatternList());
	outTiming->push_back(timerPar.Duration());

	return results;
}

// Conduct Parallel Search (TaskBased)
vector<int> ParallelSearchTasks(ConsoleUI* ui, StringSearcher* searcher, int threadQuantity, vector<long long>* outTiming)
{
	vector<int> results;

	BenchmarkTimer farmTimer;
	farmTimer.Start();

	results = searcher->SearchParallelTasks(threadQuantity);

	farmTimer.Stop();
	ui->PrintSearchTiming("Parallel CPU Search (Farm & Worker)", farmTimer.Duration());

	ui->PrintResults("Parallel CPU Search (Farm & Worker)", &results, searcher->GetPatternList());
	outTiming->push_back(farmTimer.Duration());

	return results;
}