#ifndef PINGPONG_H_
#define PINGPONG_H_

const int WARMUP = 1000;
const int NITERS = 8000;

// Run a ping-pong latency test
static inline double pingpong(std::function<void(int)> prepare, std::function<void(int)> do_work, std::function<void(int)> check)
{
    double total = 0.0;
    for (int i = 0; i < (WARMUP + NITERS); ++i) {
        // Do some sort of preparation for the work
        prepare(i);

        // Run the work and time it
        double start = MPI_Wtime();
        do_work(i);
        if (i >= WARMUP) {
            total += MPI_Wtime() - start;
        }

        // Check the result
        check(i);
    }
    return total / NITERS;
}

#endif
