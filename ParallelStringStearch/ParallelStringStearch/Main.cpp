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

	cout << "Starting Time ..." << endl;
	t1.StartTimer();

	Sleep(2000);

	t1.StopTimer();
	cout << "Timer Stopped ..." << endl;

	cout << "The test task took " << t1.Duration() << "ms!" << endl;

	t1.Reset();

	cout << "Timer Reset!" << endl;
	cout << t1.Duration() << endl;
}