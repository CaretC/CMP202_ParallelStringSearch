/*
BenchmarkTimer Class
====================
A simple reusable class for timing code execution and storing the results of mutiple runs.
The timer uses a monotonic clock to try and be as accurate as possible for this purpose.
*/

#pragma once
// Includes
// ========
#include <chrono>
#include <vector>
#include <stdexcept>

// Imports
// =======
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::vector;
using std::runtime_error;

// Type Defs
// =========
typedef std::chrono::steady_clock the_clock;

// Class
// =====
class BenchmarkTimer
{
	// Public
	// ------
	public:
		// Start the timer.
		void Start();

		// Stop the timer.
		void Stop();

		// Reset the timer duration, default non initialized value is -1.
		void Reset();

		// Save the most recent result to results vector.
		void Save();

		// Clear the results vector.
		void Clear();

		// Return all of the results from the results vector.
		vector<long long> Results();

		// Return the elapsed duration of the timer in ms.
		long long Duration();

	// Private
	// -------
	private:
		// Store the duration of the stopped timer
		long long duration_ms = -1;

		// The time point of the start
		the_clock::time_point start_time;

		// The time point of the stop
		the_clock::time_point stop_time;

		// Vector to store saved results
		vector<long long> results_ms;

		// Bool to confirm if the timer is running
		bool timerRunning = false;
};

