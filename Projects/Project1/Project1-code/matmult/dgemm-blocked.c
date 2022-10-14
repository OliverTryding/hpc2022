/* 
    Please include compiler name below (you may also include any other modules you would like to be loaded)

COMPILER= gnu

    Please include All compiler flags and libraries as you want them run. You can simply copy this over from the Makefile's first few lines
 
CC = cc
OPT = -O3
CFLAGS = -Wall -std=gnu99 $(OPT)
MKLROOT = /opt/intel/composer_xe_2013.1.117/mkl
LDLIBS = -lrt -Wl,--start-group $(MKLROOT)/lib/intel64/libmkl_intel_lp64.a $(MKLROOT)/lib/intel64/libmkl_sequential.a $(MKLROOT)/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm

*/

#include <stdlib.h>

const char* dgemm_desc = "Blocked, three-loop dgemm.";

double* transpose(double* A, int n)
{
  //Making a new array where A is transposed
  double* AT = (double*) malloc(n*n*sizeof(double));
  for (int i = 0; i < n; i++) 
  {
    for (int j = 0; j < n; j++) 
    {
        AT[i+j*n] = A[j+i*n];
    }
  }
  return AT;
}

/* This routine performs a dgemm operation
 *  C := C + A * B
 * where A, B, and C are lda-by-lda matrices stored in column-major format.
 * On exit, A and B maintain their input values. */    
void square_dgemm (int n, double* A, double* B, double* C)
{
  // Transposing A for better spacial locality
  //double* AT = transpose(A,n);

  // The code seems to be slightly faster if the transposition is moved inside.
  // Allocating a new array where A is going to be transposed
  double* AT = (double*) malloc(n*n*sizeof(double));
  for (int i = 0; i < n; i++) 
  {
    for (int j = 0; j < n; j++) 
    {
        AT[i+j*n] = A[j+i*n];
    }
  }

  // TODO: Implement the blocking optimization
  /* The size of a block */
  int s = 21;
  /* The number of blocks */
  int blocks = n / s;

  /* Three loops giving the boundries of the blocks */
  for (int u = 0; u <= blocks; u++)
  {
    for (int v = 0; v <= blocks; v++)
    {
      for (int w = 0; w <= blocks; w++)
      {
        int end_u = (u+1) * s;
        /* For each row i of Aij */
        for (int i = u * s; i<end_u && i<n; ++i)
        {
          int end_v = (v+1) * s;
          /* For each column j of Bij */
          for (int j = v * s; j<end_v && j<n; ++j)
          {
            int end_w = (w+1) * s;
            /* Compute C(i,j) */
            double cij = C[i+j*n];
            for( int k = w * s; k<end_w && k<n; k++ )
            {
              // Changed because of transposition
              cij += AT[k+i*n] * B[k+j*n];
            }
            C[i+j*n] = cij;
          }
        }
      }
    }
  }
}
