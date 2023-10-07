/* Create macros so that the matrices are stored in column-major order */

#define A(i,j) a[ (j)*lda + (i) ]
#define B(i,j) b[ (j)*ldb + (i) ]
#define C(i,j) c[ (j)*ldc + (i) ]

/* Routine for computing C = A * B + C */
// void print_row_matrix( int m, int n, double *a, int lda );
// void print_matrix( int m, int n, double *a, int lda );

void MY_MMult( int m, int n, int k, double *a, int lda, 
                                    double *b, int ldb,
                                    double *c, int ldc )
{
  int i, j, p;
  // print_row_matrix(m,k,a,lda);
  // print_row_matrix(k,n,b,ldb);

  for ( i=0; i<m; i++ ){        /* Loop over the rows of C */
    for ( j=0; j<n; j++ ){        /* Loop over the columns of C */
    // C( i,j ) = 0;
      for ( p=0; p<k; p++ ){        /* Update C( i,j ) with the inner
				       product of the ith row of A and
				       the jth column of B */
	C( i,j ) =  C( i,j ) +  A( i,p ) * B( p,j );
      }
    }
  }
  // print_row_matrix(m,n,c,ldc);
}


  
