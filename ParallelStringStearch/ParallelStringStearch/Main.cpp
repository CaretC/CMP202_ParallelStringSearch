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

// Imports
// =======
using std::cout;
using std::endl;

// Main
// ====
int main() {
	// BenchmarkTimer Test Code
	// ========================
	BenchmarkTimer t1;

	for (int i = 0; i < 5; i++)
	{
		cout << "Starting Time ..." << endl;
		t1.Start();

		Sleep(2000);

		t1.Stop();
		cout << "Timer Stopped ..." << endl;
		cout << "The test task took " << t1.Duration() << "ms!" << endl;

		t1.Save();

		cout << "Result Saved! Timer Reset!" << endl;
		cout << t1.Duration() << endl;
	}

	cout << "Looping done!" << endl;

	vector<long long> timer_results = t1.Results();

	t1.Clear();

	cout << "Results cleared!" << endl;
	// ================================

	// CsvWriter Test Code
	// ===================
	cout << "Writing testTimerResults.csv..." << endl;

	CsvWriter cw;	
	cw.WriteToFile(timer_results, "testTimerResults.csv");

	cout << "testTimerResults.csv write complete" << endl;
	// ================================

	// TextLoader Test Code
	// ====================
	cout << "Loading testText.txt..." << endl;
	
	TextLoader tl;
	string loadedTxt;

	tl.LoadFile("testText.txt", loadedTxt);

	cout << "testText.txt loaded" << endl;
	// ================================

	// Main Code
	// =========

	// ================================
}