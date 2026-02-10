// Simple ping-pong test to get estimated message latency (Shmem)
#include <iostream>
#include <functional>
#include <shmem.h>
#include <mpi.h>
#include "timing.h"

int main()
{
    shmem_init();
    int size = shmem_n_pes();
    int rank = shmem_my_pe();
    if (size != 2) {
        throw std::runtime_error{"requires exactly two processors"};
    }

    // The number being sent/received
    int* data = (int*)shmem_malloc(sizeof(int));
    int* flag = (int*)shmem_malloc(sizeof(int));

    double latency = time_work(
        [&](int iter) {
            shmem_barrier_all();
        },
        [&](int iter) {
            if (rank == 0) {
                shmem_int_p(data, iter, 1);
                shmem_quiet();
                shmem_int_p(flag, 1, 1);
            } else {
                // Wait until the flag is set
                shmem_int_wait(flag, 0);
            }
            *flag = 0;
        },
        [&](int iter) {
            if (rank == 1) {
                if (*data != iter) {
                    throw std::runtime_error{"Invalid data received"};
                }
            }
        }
    );

    std::cout << "rank=" << rank << ",latency=" << latency << "\n";

    shmem_finalize();
    return 0;
}
