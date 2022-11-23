/****************************************************************
 *                                                              *
 * This file has been written as a sample solution to an        *
 * exercise in a course given at the CSCS-USI Summer School.    *
 * It is made freely available with the understanding that      *
 * every copy of this file must include this header and that    *
 * CSCS/USI take no responsibility for the use of the enclosed  *
 * teaching material.                                           *
 *                                                              *
 * Purpose: : Parallel matrix-vector multiplication and the     *
 *            and power method                                  *
 *                                                              *
 * Contents: C-Source                                           *
 *                                                              *
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>

int hpc_verify(double* x, int n, double elapsedTime) {
    int i;
    double answer = sqrt(n);
    double diff = 1;
    int correct = 1;

    for (i = 0; i < n; i++) {
        // make sure each element of the vector x equals sqrt(n).
        // to allow for errors in floating point calculations, close is good enough.
        diff = x[i] - answer;
        if (diff < 0)
            diff = -diff;

        if (diff > 0.00001 || isnan(diff)) {
            correct = 0;
            break;
        }
    }

    // I will be using the elapsedTime argument here.

    return correct;
}

double* hpc_generateMatrix(int n, int startrow, int numrows) {
    double* A;
    // int i;
    // int diag;

    A = (double*)calloc(n * numrows, sizeof(double));

    for (int i = 0; i < numrows; i++) {
        int diag = startrow + i;

        A[i * n + diag] = n;
    }

    return A;
}

double norm(double* vec, int n) {
    double norm = 0;
    for (int i=0; i<n; i++) {
        norm += pow(vec[i],2);
    }
    // norm = sqrt(norm);
    return (sqrt(norm));
}

void matVec(double* M, double* vec, double* x, int n, int p) {

    MPI_Bcast(vec, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double prod[p];

    for (int i=0; i<p; i++) {
        for (int j=0; j<n; j++) {
            prod[i] += M[i*n + j] * vec[j];
        }
    }

    MPI_Gather(prod, p, MPI_DOUBLE, x, p, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // return (x);
}

void powerMethod(double* M, double* x, int iterations, int n, int p) {
    double z[n];
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank==0) {
        for (int i=0; i<n; i++) {
            x[i] = 1.0;// (double)rand();
        }
    }

    for (int k=0; k < iterations; k++) {

        double x_norm = norm(x,n);
        if (my_rank==0) {
            for (int i=0; i<n; i++) {
                x[i] = x[i] / x_norm;
            }
        }
        if (my_rank==1) {
            for (int i=0; i<p; i++) {
                for (int j=0; j<n; j++) {
                    printf("%f ", M[n*i + j]);
                }
            }
        }

        matVec(M,x,z,n,p);
        if (my_rank==0) {
            for (int i=0; i<n; i++) {
                x[i] = z[i];
            }
        }
    }

    // return (x);
}

int main (int argc, char *argv[])
{
    int my_rank, size;
    // int snd_buf, rcv_buf;
    // int right, left;
    // int sum, i;
    int m = 16;
    int iter = 100;
    double x[m];

    //srand(time(NULL));

    MPI_Status  status;
    MPI_Request request;


    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //  my_rank = 0;
    //  size = 1;

    /* This subproject is about to write a parallel program to
       multiply a matrix A by a vector x, and to use this routine in
       an implementation of the power method to find the absolute
       value of the largest eigenvalue of the matrix. Your code will
       call routines that we supply to generate matrices, record
       timings, and validate the answer.
    */

    int partition = m / size;

    double* A = hpc_generateMatrix(m, my_rank * partition, partition);

    // double* x = powerMethod(A,1000,m);

    double start = MPI_Wtime();
    powerMethod(A,x,iter,m,partition);
    double time = MPI_Wtime() - start;

    MPI_Finalize();
    
    if (my_rank == 0) {
        printf("%d processor finished the task in %f seconds with exit code %d.\n", size, time, hpc_verify(x,m,0.0));
    }

    return 0;
}
