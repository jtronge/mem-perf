#!/bin/sh
#SBATCH --exclusive
#SBATCH --mem=0
#SBATCH -N 2
#SBATCH -n 2
#SBATCH -c 1
#SBATCH --constraint graniterapids

. ./env
srun -o output/bw-internode-graniterapids.out -N 2 -n 2 -c 1 ./bw_mpi 4096
