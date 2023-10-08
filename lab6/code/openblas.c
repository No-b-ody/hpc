#include <cblas.h>
void MY_MMult( int m, int n, int k, double *a, int lda, 
                                    double *b, int ldb,
                                    double *c, int ldc )
{
	cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,n,n,n,1,a, n, b, n,1,c,n);
}


