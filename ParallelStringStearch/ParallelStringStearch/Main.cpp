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
	// BenchmarkTimer Test Code
	// ========================
	//BenchmarkTimer t1;

	//for (int i = 0; i < 5; i++)
	//{
	//	cout << "Starting Time ..." << endl;
	//	t1.Start();

	//	Sleep(2000);

	//	t1.Stop();
	//	cout << "Timer Stopped ..." << endl;
	//	cout << "The test task took " << t1.Duration() << "ms!" << endl;

	//	t1.Save();

	//	cout << "Result Saved! Timer Reset!" << endl;
	//	cout << t1.Duration() << endl;
	//}

	//cout << "Looping done!" << endl;

	//vector<long long> timer_results = t1.Results();

	//t1.Clear();

	//cout << "Results cleared!" << endl;
	// ================================

	// CsvWriter Test Code
	// ===================
	//cout << "Writing testTimerResults.csv..." << endl;

	//CsvWriter cw;	
	//cw.WriteToFile(timer_results, "testTimerResults.csv");

	//cout << "testTimerResults.csv write complete" << endl;
	// ================================

	// TextLoader Test Code
	// ====================
	//string textFile = "AliceInWonderland.txt";
	string textFile = "testText.txt";
	cout << "Loading " << textFile << "..." << endl;
	
	TextLoader tl;
	string loadedTxt;

	tl.LoadFile(textFile, loadedTxt);

	cout << textFile << " loaded" << endl;
	// ================================

	// PatternListLoader Test Code
	// ===========================
	cout << "Load textPatterns.txt..." << endl;

	vector<string> patternList;

	PatternListLoader PattLoader;
	PattLoader.LoadPatternList("textPatterns.txt", patternList);
	
	cout << "textPatterns.txt loaded" << endl;
	// ================================

	//cout << "Test Complete!" << endl;

	// Boyer-Moore-Horspool Test Code
	// ==============================
	//cout << "Conducting string search" << endl;

	//int results = BoyerMooreHorspool("the", loadedTxt);

	//cout << "String search complete " << results << " pattern matches found" << endl;
	// ================================

	// Main Code
	// =========
	int numberOfPatterns = patternList.size();

	// Test pattern array
	string patterns[3] = { "the", "a", "time" };

	// Sequencial
	// ----------
	cout << "Staring sequencial search..." << endl;

	BenchmarkTimer timerSeq;
	timerSeq.Start();

	for (int i = 0; i < numberOfPatterns; i++)
	{
		BoyerMooreHorspool(patternList[i], loadedTxt);
	}

	timerSeq.Stop();

	cout << "Sequencial search completed in " << timerSeq.Duration() << "ms" << endl;



	// Parallel
	// --------
	cout << "Starting parallel search..." << endl;

	BenchmarkTimer timerPar;
	timerPar.Start();

	//Define the number of threads to use
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
	cout << "Parallel search complete!" << "Search took " << timerPar.Duration() << "ms" << endl;
	// ================================
}

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
			//cout << "Match found at position " << i << endl;
		}
		else
		{
			//cout << "No match in the tet found!" << endl;
		}
	}

	return matches;
}