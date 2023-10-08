#include <omp.h>
#define A(i,j) a[ (j)*lda + (i) ]
#define B(i,j) b[ (j)*ldb + (i) ]
#define C(i,j) c[ (j)*ldc + (i) ]
void MY_MMult( int m, int n, int k, double *a, int lda, 
                                    double *b, int ldb,
                                    double *c, int ldc )
{
  #pragma omp parallel for
  for (int i=0; i<m; i++ ){        /* Loop over the rows of C */
    for (int j=0; j<n; j++ ){        /* Loop over the columns of C */
    // C( i,j ) = 0;
      for (int p=0; p<k; p++ ){        
      	      C( i,j ) =  C( i,j ) +  A( i,p ) * B( p,j );
      }
    }
  }
}

