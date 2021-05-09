/*
CMP 202 Coursework - Parallel String Search
*/

// Includes
// ========
#include <iostream>
#include <string>
#include <unordered_map>

#include "ConsoleUI.h"
#include "BenchmarkTimer.h"
#include "CsvWriter.h"
#include "TextLoader.h"
#include "PatternListLoader.h"
#include "StringSearcher.h"

// Imports
// =======
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

// Function Prototypes
// ===================
void PrintWelcomeScreen(ConsoleUI* ui);
string LoadSearchTextFile(ConsoleUI* ui, string filePath);
vector<string> LoadPatternListFile(ConsoleUI* ui, string filePath);
vector<int> SequentialSearch(ConsoleUI* ui, StringSearcher* searcher, long long* outTiming);
unordered_map<string, int> ParallelSearchTasks(ConsoleUI* ui, StringSearcher* searcher, int threadQuantity, vector<long long>* outTiming);

// Globals
// =======
// Print results
bool printResults = true;

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
	// Search Text 'The King James version of the bible' taken from large.zip from https://corpus.canterbury.ac.nz/descriptions/
	searchText = LoadSearchTextFile(&ui, "SearchTexts/bible.txt");

	// Load Pattern List
	// -----------------
	// Custom compiled pattern list of the top 100 most common english words to search
	patternList = LoadPatternListFile(&ui, "PatternLists/100-Common.txt");

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
		// Parallel Search (Task Based)
		// ----------------------------
		unordered_map<string, int> taskParallelResults = ParallelSearchTasks(&ui, &Searcher, threads, &timingTask);
	}

	cw.WriteToFile(timingSeq, timingTask, "varyThreadsTiming.csv");

	// Vary Patterns
	// --------------
	for (int patterns = 1; patterns <= patternList.size(); patterns++)
	{
		string msg = "Searching for " + patterns;
		ui.PrintMessage(msg);
		vector<string> varyPatt;

		for (int i = 0; i < patterns; i++)
		{
			varyPatt.push_back(patternList[i]);			
		}

		StringSearcher pattSearch(&searchText, &varyPatt, &ui);
		unordered_map<string, int> taskParallelResults = ParallelSearchTasks(&ui, &pattSearch, 8, &timingTaskPatt);
	}

	cw.WriteToFile(timingTaskPatt, "varyPatternTiming.csv");
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

	if (printResults)
	{
		ui->PrintResults("Sequential CPU Search", &results, searcher->GetPatternList());
	}

	return results;
}

// Conduct Parallel Search (TaskBased)
unordered_map<string, int> ParallelSearchTasks(ConsoleUI* ui, StringSearcher* searcher, int threadQuantity, vector<long long>* outTiming)
{
	unordered_map<string, int> results;

	BenchmarkTimer farmTimer;
	farmTimer.Start();

	results = searcher->SearchParallelTasks(threadQuantity);

	farmTimer.Stop();
	ui->PrintSearchTiming("Parallel CPU Search (Farm & Worker)", farmTimer.Duration());

	if (printResults)
	{
		ui->PrintResults("Parallel CPU Search (Farm & Worker)", &results, searcher->GetPatternList());
	}

	outTiming->push_back(farmTimer.Duration());

	return results;
}