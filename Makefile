MPI_CXX = mpicxx
SHMEM_CXX = oshc++

all: pingpong_mpi pingpong_shmem
.PHONY: all

pingpong_mpi: pingpong_mpi.cc
	$(MPI_CXX) -o $@ $<

pingpong_shmem: pingpong_shmem.cc
	$(SHMEM_CXX) -o $@ $<

clean:
	rm -rf pingpong_mpi pingpong_shmem
.PHONY: clean
