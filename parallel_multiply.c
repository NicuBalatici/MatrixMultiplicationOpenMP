#include<stdio.h>
#include<math.h>
#include<omp.h>
#include"header.h"

//matrix multiplication variants (parallel version) corresponding to all 6 permutations of (i,j,k): i-j-k, i-k-j, j-i-k, j-k-i, k-i-j, k-j-i

void parallel_multiply_ijk(int nthreads, int chunk)
{
    int i, j, k;

    #pragma omp parallel num_threads(nthreads) private(i, j, k)
    {
        #pragma omp for schedule(static, chunk)
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++) 
            {
                result_p[i][j] = 0;
            }
        }

        #pragma omp for schedule(static, chunk)
        for (i = 0; i < N; i++) 
        {
            for (j = 0; j < N; j++) 
            {
                for (k = 0; k < N; k++) 
                {
                    result_p[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }
}

void parallel_multiply_ikj(int nthreads, int chunk)
{
    int i, j, k;

    #pragma omp parallel num_threads(nthreads) private(i, j, k)
    {
        #pragma omp for schedule(static, chunk)
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                result_p[i][j] = 0;
            }
        }

        #pragma omp for schedule(static, chunk)
        for (i = 0; i < N; i++)
        {
            for (k = 0; k < N; k++)
            {
                for (j = 0; j < N; j++)
                {
                    result_p[i][j] +=  a[i][k] * b[k][j];
                }
            }
        }
    }
}

void parallel_multiply_jik(int nthreads, int chunk)
{
    int i, j, k;
    #pragma omp parallel num_threads(nthreads), private(i, j, k)
    {
        #pragma omp for schedule(static, chunk)
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                result_p[i][j] = 0;
            }
        }
        
        #pragma omp for schedule(static, chunk)
        for (j = 0; j < N; j++)
        {
            for (i = 0; i < N; i++)
            {
                for (k = 0; k < N; k++)
                {
                    result_p[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }
}

void parallel_multiply_jki(int nthreads, int chunk)
{
    int i, j, k;
    #pragma omp parallel num_threads(nthreads), private(i, j, k)
    {
    #pragma omp for schedule(static, chunk)
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                result_p[i][j] = 0;
            }
        }

    #pragma omp for schedule(static, chunk)
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N; k++)
            {
                for (i = 0; i < N; i++)
                {
                    result_p[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }
}

void parallel_multiply_kij(int nthreads, int chunk)
{
    int i, j, k;
    #pragma omp parallel num_threads(nthreads), private(i, j, k)
    {
        #pragma omp for schedule(static, chunk)
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                result_p[i][j] = 0;
            }
        }
        #pragma omp for schedule(static, chunk)
        for (k = 0; k < N; k++)
        {
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < N; j++)
                {
                    result_p[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }
}

void parallel_multiply_kji(int nthreads, int chunk)
{
    int i=0, j=0, k=0;
    #pragma omp parallel num_threads(nthreads), private(i, j, k)
    {
    #pragma omp for schedule(static, chunk)
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                result_p[i][j] = 0;
            }
        }
    #pragma omp for schedule(static, chunk)
        for (k = 0; k < N; k++)
        {
            for (j = 0; j < N; j++)
            {
                for (i = 0; i < N; i++)
                {
                    result_p[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }
}

//the blocked version of matrix multiplication
void parallel_blocked(int nthreads, int chunk)
{
    int i, j, k;
    #pragma omp parallel num_threads(nthreads), private(i, j, k)
    {
        if(N*N % chunk==0)
        {
            #pragma omp for schedule(dynamic, chunk)
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < N; j++)
                {
                    result_s2[i][j]=0;
                    for (k = 0; k < N; k++)
                    {
                        result_p2[i][j] += a[i][k] * b[k][j];
                    }
                }
            }
        }
        else
        {
            #pragma omp for schedule(static, chunk)
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < N; j++)
                {
                    result_s2[i][j]=0;
                    for (k = 0; k < N; k++)
                    {
                        result_p2[i][j] += a[i][k] * b[k][j];
                    }
                }
            }
        }
    }
}