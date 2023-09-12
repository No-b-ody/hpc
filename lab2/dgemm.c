#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "time.h"
#include "f77blas.h"
#include <cblas.h>
void dgemm(int n, double A[][n], double B[][n], double C[][n])
{
    for (int i = 0; i < n; i++)
    { // C[i]
        for (int j = 0; j < n; j++)
        { // C[i][j]
            C[i][j] = 0;
            for (int p = 0; p < n; p++)
            {
                C[i][j] += A[i][p] * B[p][j];
            }
        }
    }
}
int main(int argc, char *argv[])
{
    int i;
    printf("test!\n");
    if (argc < 2)
    {
        printf("Input Error\n");
        return 1;
    }

    int n = atoi(argv[1]);
    int sizeofa = n * n;
    int sizeofb = n * n;
    int sizeofc = n * n;
    struct timeval start, finish;
    double duration;
    double *A = (double *)malloc(sizeof(double) * sizeofa);
    double *B = (double *)malloc(sizeof(double) * sizeofb);
    double *C = (double *)malloc(sizeof(double) * sizeofc);
    srand((unsigned)time(NULL));
    for (i = 0; i < sizeofa; i++)
        A[i] = (rand() % 100) / 10.0;

    for (i = 0; i < sizeofb; i++)
        B[i] = (rand() % 100) / 10.0;

    for (i = 0; i < sizeofc; i++)
        C[i] = (rand() % 100) / 10.0;
    // #if 0
    printf("n=%d,sizeofc=%d\n", n, sizeofc);
    FILE *fp;
    gettimeofday(&start, NULL);
    dgemm(n, A, B, C);
    gettimeofday(&finish, NULL);

    duration = ((double)(finish.tv_sec - start.tv_sec) * 1000000 + (double)(finish.tv_usec - start.tv_usec)) / 1000000;
    double gflops = 2.0 * n * n * n;
    gflops = gflops / duration * 1.0e-6 / 1000;

    fp = fopen("timeDGEMM.txt", "a");
    fprintf(fp, "native:     %dx%dx%d\t%lf s\t%lf GFLOPS\n",n, n, n, duration, gflops);

    gflops = 2.0 * n * n * n;
    gettimeofday(&start, NULL);
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,n,n,n,1,A, n, B, n,1,C,n);
    gettimeofday(&finish, NULL);

    duration = ((double)(finish.tv_sec - start.tv_sec) * 1000000 + (double)(finish.tv_usec - start.tv_usec)) / 1000000;
    gflops = gflops / duration * 1.0e-6 / 1000;

    fprintf(fp, "OpenBlas:  %dx%dx%d\t%lf s\t%lf GFLOPS\n", n, n, n, duration, gflops);
    fclose(fp);
    free(A);
    free(B);
    free(C);
    return 0;
}  
