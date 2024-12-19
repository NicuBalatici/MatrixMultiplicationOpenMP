#include<stdio.h>
#include<math.h>
#include"header.h"

//matrix multiplication variants (serial version) corresponding to all 6 permutations of (i,j,k): i-j-k, i-k-j, j-i-k, j-k-i, k-i-j, k-j-i

void serial_multiply_ijk(void)
{
    int i, j, k;
    double aik = 0;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            result_s[i][j] = 0;
        }
    }

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N; k++)
            {
                aik = a[i][k];
                result_s[i][j] += aik * b[k][j];
            }
        }
    }
}

void serial_multiply_ikj(void)
{
    int i, j, k;
    double aik;

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            result_s2[j][i] = 0;            
        }
    }

    for(i=0; i<N; i++)
    {
        for(k=0; k<N; k++)
        {
            for(j=0; j<N; j++)
            {
                aik=a[i][k];
                result_s2[i][j]+=aik*b[k][j];
            }
        }
    }
}

void serial_multiply_jik(void)
{
    int i, j, k;
    double aik;

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            result_s2[j][i] = 0;
        }
    }

    for(j=0; j<N; j++)
    {
        for (i=0; i<N; i++)
        {
            for (k=0; k<N; k++)
            {
                aik=a[i][k];
                result_s2[i][j]+=aik*b[k][j];
            }
        }
    }
}

void serial_multiply_jki(void)
{
    int i=0, j=0, k=0;
    double aik=0;
    
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            result_s2[i][j] = 0;
        }
    }

    for (j = 0; j < N; j++) 
    {
        for (k = 0; k < N; k++) 
        {
            for (i = 0; i < N; i++) 
            {
                aik = a[i][k];
                result_s2[i][j] += aik * b[k][j];
            }
        }
    }
}

void serial_multiply_kij(void)
{
    int i, j, k;
    double aik = 0;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            result_s2[i][j] = 0;
        }
    }

    for (k = 0; k < N; k++)
    {
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                aik = a[i][k];
                result_s2[i][j] += aik * b[k][j];
            }
        }
    }
}

void serial_multiply_kji(void)
{
    int i=0, j=0, k=0;
    double aik=0;
    
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            result_s2[i][j]=0;
        }
    }

    for (k = 0; k < N; k++)
    {
        for (j = 0; j < N; j++)
        {
            for (i = 0; i < N; i++)
            {
                aik = a[i][k];
                result_s2[i][j] += aik * b[k][j];
            }
        }
    }
}

//the blocked version of matrix multiplication

void serial_blocked(void)
{
    int i, j, k;
    
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            result_s2[i][j] = 0;
            for (k = 0; k < N; k++)
            {
                result_s2[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}