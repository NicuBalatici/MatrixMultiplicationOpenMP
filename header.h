#ifndef header
#define header

#include<time.h>
#define N 1000
#define EPSILON 0.000001
double a[N][N], b[N][N], result_s[N][N], result_s2[N][N], result_p[N][N], result_p2[N][N];

//location of the functions: serial_multiply.c
void serial_multiply_ijk(void);
void serial_multiply_ikj(void);
void serial_multiply_jik(void);
void serial_multiply_jki(void);
void serial_multiply_kij(void);
void serial_multiply_kji(void);
void serial_blocked(void);

//location of the functions: matrix_multiplication.c
int Equal_matrixes(double mat1[N][N], double mat2[N][N]);
void Generate_matrix(char *prompt, double mat[N][N]);
double min(double x[], int size);
void perfect_value(double *cpu_time_used_blocked);
void time_serial_functions(clock_t *start, clock_t *end, double *cpu_time_used);
void time_parallel_functions(clock_t *start, clock_t *end, double *cpu_time_used);
void good_block_size(clock_t *start_blocked2, clock_t *end_blocked2, double *cpu_time_used_blocked2);
void comparing_matrix();

//location of the functions: parallel_multiply.c
void parallel_multiply_ijk(int nthreads, int chunk);
void parallel_multiply_ikj(int nthreads, int chunk);
void parallel_multiply_jik(int nthreads, int chunk);
void parallel_multiply_jki(int nthreads, int chunk);
void parallel_multiply_kij(int nthreads, int chunk);
void parallel_multiply_kji(int nthreads, int chunk);
void parallel_blocked(int nthreads, int chunk);

#endif