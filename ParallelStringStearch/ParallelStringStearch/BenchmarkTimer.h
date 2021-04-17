#pragma once
// Includes
// ========
#include <chrono>
#include <vector>

// Imports
// =======
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::vector;

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
		void StartTimer();

		// Stop the timer.
		void StopTimer();

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
		long long duration_ms = -1;
		the_clock::time_point start_time;
		the_clock::time_point stop_time;
		vector<long long> results_ms;
};

