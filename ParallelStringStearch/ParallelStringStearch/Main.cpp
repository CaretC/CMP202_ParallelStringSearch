/*
CMP 202 Coursework - Parallel String Search
*/

// Includes
// ========
#include <iostream>
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

// Function Prototypes
// ===================
void BoyerMooreHorspool(string pattern, string& text);

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
	cout << "Loading testText.txt..." << endl;
	
	TextLoader tl;
	string loadedTxt;

	tl.LoadFile("testText.txt", loadedTxt);

	cout << "testText.txt loaded" << endl;
	// ================================

	// PatternListLoader Test Code
	// ===========================
	cout << "Load textPatterns.txt..." << endl;

	vector<string> patternList;

	PatternListLoader PattLoader;
	PattLoader.LoadPatternList("textPatterns.txt", patternList);
	
	cout << "textPatterns.txt loaded" << endl;
	// ================================

	cout << "Test Complete!" << endl;

	// Boyer-Moore-Horspool Test Code
	// ==============================
	BoyerMooreHorspool("This", loadedTxt);

	// ================================

	// Main Code
	// =========

	// ================================
}

// Boyer-Moore-Horspool
// ====================
// A very basic implementation of the boyer moore horspool algorithm to search for a single pattern in a single 
// continuous string.
void BoyerMooreHorspool(string pattern, string& text)
{
	// Pre-process the pattern into char table
	CharTable pattTable(pattern);
	cout << "Pattern pre-processed" << endl;

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
			cout << "Match found at position " << i << endl;
		}
		else
		{
			//cout << "No match in the tet found!" << endl;
		}
	}
}