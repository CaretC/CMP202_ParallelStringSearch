#pragma once
// Includes
// ========
#include <chrono>

// Imports
// =======
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

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
		void StartTimer();

		void StopTimer();

		void Reset();

		long long Duration();

	// Private
	// -------
	private:
		long long duration_ms = -1;
		the_clock::time_point start_time;
		the_clock::time_point stop_time;
};

