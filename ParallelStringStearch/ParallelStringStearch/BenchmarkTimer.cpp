#include "BenchmarkTimer.h"

// Public Functions
// ================
// Start the timer.
void BenchmarkTimer::StartTimer()
{
    start_time = the_clock::now();
}

// Stop the timer.
void BenchmarkTimer::StopTimer()
{
    stop_time = the_clock::now();
    duration_ms = duration_cast<milliseconds>(stop_time - start_time).count();
}

// Reset the timer duration, default non initialized value is -1.
void BenchmarkTimer::Reset()
{
    duration_ms = -1;
}

// Save the most recent result to results vector. Will reset time in the process.
void BenchmarkTimer::Save()
{
    results_ms.push_back(duration_ms);
    Reset();
}

// Clear the results vector.
void BenchmarkTimer::Clear()
{
    results_ms.clear();
}

// Return all of the results from the results vector.
vector<long long> BenchmarkTimer::Results()
{
    return results_ms;
}

// Return the elapsed duration of the timer in ms.
long long BenchmarkTimer::Duration()
{
    return duration_ms;
}
