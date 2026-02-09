#!/bin/sh
#SBATCH --exclusive
#SBATCH --mem=0
#SBATCH -N 1
#SBATCH -n 2
#SBATCH -c 1
#SBATCH --constraint graniterapids

. ./env
srun -o output/latency-graniterapids.out -N 1 -n 2 -c 1 ./latency_mpi
