// Simple ping-pong test to get estimated message latency (MPI)
#include <iostream>
#include <functional>
#include <mpi.h>
#include "timing.h"

int main()
{
    MPI_Init(nullptr, nullptr);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (size != 2) {
        throw std::runtime_error{"requires exactly two processors"};
    }

    // The number being sent/received
    int x = 0;

    double latency = time_work(
        [&](int iter) {
            if (rank == 0) {
                x = iter;
            }
        },
        [&](int iter) {
            if (rank == 0) {
                MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            } else {
                MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        },
        [&](int iter) {
            if (x != iter) {
                throw std::runtime_error{"something went wrong with send"};
            }
        }
    );

    std::cout << "rank=" << rank << ",latency=" << latency << "\n";

    MPI_Finalize();
    return 0;
}
