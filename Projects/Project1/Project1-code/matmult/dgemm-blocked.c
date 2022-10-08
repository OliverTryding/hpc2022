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

const char* dgemm_desc = "Naive, three-loop dgemm.";

/* This routine performs a dgemm operation
 *  C := C + A * B
 * where A, B, and C are lda-by-lda matrices stored in column-major format.
 * On exit, A and B maintain their input values. */    
void square_dgemm (int n, double* A, double* B, double* C)
{
  // TODO: Implement the blocking optimization
  int s = 22;
  int blocks = n / s;

  for (int u = 0; u <= blocks; u++)
  {
    for (int v = 0; v <= blocks; v++)
    {
      for (int w = 0; w <= blocks; w++)
      {
        int end_u = (u+1) * s;
        /* For each row i of A */
        for (int i = u * s; i<end_u && i<n; ++i)
        {
          int end_v = (v+1) * s;
          /* For each column j of B */
          for (int j = v * s; j<end_v && j<n; ++j)
          {
            int end_w = (w+1) * s;
            /* Compute C(i,j) */
            double cij = C[i+j*n];
            for( int k = w * s; k<end_w && k<n; k++ )
            {
              cij += A[i+k*n] * B[k+j*n];
            }
            C[i+j*n] = cij;
          }
        }
      }
    }
  }
}
