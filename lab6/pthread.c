#include <assert.h>
#include <pthread.h>
#include <unistd.h>
typedef struct 
{
    double *A;
    double *B;
    double *C;
    int alow;
    int ahigh;
    int blow;
    int bhigh;
    int k;
    int n;
}agv;

void *pthread(void *arg)
{
    agv *P = (agv *)arg;
    for (int i = P->alow-1; i < P->ahigh; i++)
    {
        for (int j = P->blow; j < P->bhigh; j++)
        {
            P->C[i*P->k+j] = 0;
            for (int p = 0; p < P->k; p++)
            {
                     P->C[i*P->k+j] += P->A[i*P->k+p] * P->B[p*P->n+j];
            }
        }
    }
}//double *A,double *B,double *C,int alow,int ahigh,int blow,int bhigh,int k ,int n

void MY_MMult( int m, int n, int k, double *a, int lda,
                                    double *b, int ldb,
                                    double *c, int ldc )
{
    int i=m/2;
    int rc;
    pthread_t  p1, p2;
    agv c1={a,b,c,1,i,1,n,k,n};
    agv c2={a,b,c,i+1,m,1,n,k,n};
    rc = pthread_create(&p1, NULL, pthread, &c1); assert(rc == 0);
    rc = pthread_create(&p2, NULL, pthread, &c2); assert(rc == 0);
    rc = pthread_join(p1, NULL); assert(rc == 0); 
    rc = pthread_join(p2, NULL); assert(rc == 0); 
}




