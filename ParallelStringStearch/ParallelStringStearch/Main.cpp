/*
CMP 202 Coursework - Parallel String Search
*/

// Includes
// ========
#include <iostream>
#include <thread>
#include <string>
#include <Windows.h> // For Testing!

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

// Thread struct
// =============
struct SearchArgs
{
	string pattern;
	string text;
};

// Function Prototypes
// ===================
int BoyerMooreHorspool(string pattern, string& text);
void threadBM(SearchArgs args);

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
		BoyerMooreHorspool(patternList[i], loadedTxt);
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

	// Threads message
	//cout << "This program will use " << numThreads << " to process patterns" << endl;

	// Make threads array to store the threads
	vector<thread> threads;

	// Argument for the threads
	SearchArgs threadArgs;	
	threadArgs.text = loadedTxt;

	// Populate the threads
	for (int i = 0; i < numThreads; i++)
	{
		threadArgs.pattern = patternList[i];
		threads.push_back(thread(threadBM, threadArgs));
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



// Thread BM
void threadBM(SearchArgs args)
{
	int matches = BoyerMooreHorspool(args.pattern, args.text);
	//cout << matches << endl;
}



// Boyer-Moore-Horspool
// ====================
// A very basic implementation of the boyer moore horspool algorithm to search for a single pattern in a single 
// continuous string.
int BoyerMooreHorspool(string pattern, string& text)
{
	// Valid matches
	int matches = 0;

	// Pre-process the pattern into char table
	CharTable pattTable(pattern);
	//cout << "Pattern pre-processed" << endl;

	// Search the text for the string
	for (int i = 0; i < text.length() - pattTable.Length(); i++)
	{
		// Check if the tail character is in the pattTable
		int skipStep = pattTable.In(text[i + pattTable.Length() - 1]);

		if (skipStep != 0)
		{
			i += skipStep - 1;
			continue;
		}

		// Check for match
		int j;
		for (j = 0; j < pattTable.Length(); j++)
		{
			if (text[i + j] != pattern[j])
			{
				// This is not a match
				break;
			}
		}

		// Check if the match loop exited after finding string or breaking
		if (j == pattTable.Length())
		{
			matches++;
			// TODO: Save this somewhere
			//cout << "Match found at position " << i << endl;
		}
		else
		{
			//cout << "No match in the text found!" << endl;
		}
	}

	return matches;
}