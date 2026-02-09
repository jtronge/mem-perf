#ifndef TIMING_H_
#define TIMING_H_

#include <chrono>

const int WARMUP = 10;
const int NITERS = 20;

// Run a ping-pong latency test, returning average time in seconds.
static inline double time_work(std::function<void(int)> prepare, std::function<void(int)> do_work, std::function<void(int)> check)
{
    double total = 0.0;
    for (int i = 0; i < (WARMUP + NITERS); ++i) {
        // Do some sort of preparation for the work
        prepare(i);

        // Run the work and time it
        auto time_start = std::chrono::high_resolution_clock::now();
        do_work(i);
        if (i >= WARMUP) {
            auto time_stop = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = time_stop - time_start;
            total += duration.count();
            // total += std::chrono::duration_cast<double, std::chrono::seconds>(duration);
            // total += std::chrono::duration_cast<double, std::chrono::seconds>(time_stop - time_start).count();
        }

        // Check the result
        check(i);
    }
    return total / NITERS;
}

#endif
