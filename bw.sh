#!/bin/sh
#SBATCH --exclusive
#SBATCH --mem=0
#SBATCH -n 1
#SBATCH -c 1
#SBATCH --constraint graniterapids

. ./env
./bw 4096 > output/mem-bw-graniterapids.out
