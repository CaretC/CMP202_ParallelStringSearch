/*
BenchmarkTimer Class
====================
A simple reusable class for timing code execution and storing the results of mutiple runs.
The timer uses a monotonic clock to try and be as accurate as possible for this purpose.
*/

// Includes
// ========
#include "BenchmarkTimer.h"

// Public Functions
// ================
// Start the timer.
void BenchmarkTimer::Start()
{
    // If the timer is running stop it and save the current result
    if (timerRunning)
    {
        Stop();
        Save();
    }

    start_time = the_clock::now();
    timerRunning = true;
}

// Stop the timer.
void BenchmarkTimer::Stop()
{
    if (timerRunning)
    {
        stop_time = the_clock::now();
        duration_ms = duration_cast<milliseconds>(stop_time - start_time).count();
        timerRunning = false;
    }
    else
    {
        // Throw Error
        throw runtime_error("BenchmarkTimer::Stop() called while the timer is not running.");
    }
}

// Reset the timer duration, default non initialized value is -1.
void BenchmarkTimer::Reset()
{
    // If the timer is running stop it
    if (timerRunning)
    {
        Stop();
    }

    duration_ms = -1;
}

// Save the most recent result to results vector. Will reset time in the process.
void BenchmarkTimer::Save()
{
    // If the timer is running stop it
    if (timerRunning)
    {
        Stop();
    }

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
