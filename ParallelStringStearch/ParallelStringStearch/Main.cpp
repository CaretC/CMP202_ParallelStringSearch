/*
CMP 202 Coursework - Parallel String Search
*/

// Includes
// ========
#include <iostream>
#include <Windows.h> // For Testing!

#include "BenchmarkTimer.h"

// Imports
// =======
using std::cout;
using std::endl;

// Main
// ====
int main() {
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
}