CXX = g++
MPI_CXX = mpicxx
SHMEM_CXX = oshc++

all: latency_mpi latency_shmem bw_mpi bw
.PHONY: all

latency_mpi: latency_mpi.cc timing.h
	$(MPI_CXX) -o $@ $<

latency_shmem: latency_shmem.cc timing.h
	$(SHMEM_CXX) -o $@ $<

bw_mpi: bw_mpi.cc timing.h
	$(MPI_CXX) -o $@ $<

bw: bw.cc timing.h
	$(CXX) -o $@ $<

clean:
	rm -rf latency_mpi latency_shmem bw_mpi bw
.PHONY: clean
