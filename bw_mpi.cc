// Simple communication bandwidth test in MPI
#include <iostream>
#include <vector>
#include <functional>
#include <cstdint>
#include <mpi.h>
#include "timing.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [BUF_SIZE]\n";
        std::cerr << "  BUF_SIZE: buffer size in MB\n";
        return 1;
    }

    MPI_Init(nullptr, nullptr);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    uint64_t total_mb = std::stoul(argv[1]);
    uint64_t total_bytes = total_mb * 1024 * 1024;
    uint64_t count = total_bytes / sizeof(int);
    std::vector<int> data(count, 0);

    double time = time_work(
        [&](int iter) {
            if (rank == 0) {
                for (auto& x : data) {
                    x = iter;
                }
            }
        },
        [&](int iter) {
            if (rank == 0) {
                MPI_Send(data.data(), count, MPI_INT, 1, 0, MPI_COMM_WORLD);
            } else {
                MPI_Recv(data.data(), count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        },
        [&](int iter) {
            for (auto& x : data) {
                if (x != iter) {
                    throw std::runtime_error{"invalid data sent or received"};
                }
            }
        }
    );

    double bw = double(total_mb) / time;
    std::cout << "rank=" << rank << ",bw=" << bw << "MiB/s\n";

    MPI_Finalize();
    return 0;
}
