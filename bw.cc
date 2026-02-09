// Simple memory bandwidth test
#include <iostream>
#include <vector>
#include <functional>
#include <cstring>
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

    uint64_t total_mb = std::stoul(argv[1]);
    uint64_t total_bytes = total_mb * 1024 * 1024;
    uint64_t count = total_bytes / sizeof(int);
    std::vector<int> a(count, 0);
    std::vector<int> b(count, 0);

    double time = time_work(
        [&](int iter) {
            for (auto& x : a) {
                x = iter;
            }
        },
        [&](int iter) {
            std::memcpy(b.data(), a.data(), a.size() * sizeof(int));
        },
        [&](int iter) {
            for (auto& x : b) {
                if (x != iter) {
                    throw std::runtime_error{"invalid data copied"};
                }
            }
        }
    );

    double bw = double(total_mb) / time;
    std::cout << "bw=" << bw << "MiB/s\n";
    return 0;
}
