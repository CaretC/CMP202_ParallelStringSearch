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

// Return the elapsed duration of the timer in ms.
long long BenchmarkTimer::Duration()
{
    return duration_ms;
}
