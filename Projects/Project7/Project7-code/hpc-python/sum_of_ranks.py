import numpy as np
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

# Slow
# result = comm.allreduce(rank, MPI.SUM)

# Fast
result = np.array(0)
comm.Allreduce(np.array(rank), result, MPI.SUM)

if rank == 0:
    print(f"The sum of ranks is {result}.")