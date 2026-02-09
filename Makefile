MPI_CXX = mpicxx
SHMEM_CXX = oshc++

all: latency_mpi latency_shmem bw_mpi
.PHONY: all

latency_mpi: latency_mpi.cc pingpong.h
	$(MPI_CXX) -o $@ $<

latency_shmem: latency_shmem.cc pingpong.h
	$(SHMEM_CXX) -o $@ $<

bw_mpi: bw_mpi.cc pingpong.h
	$(MPI_CXX) -o $@ $<

clean:
	rm -rf latency_mpi latency_shmem
.PHONY: clean
