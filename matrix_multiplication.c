#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"header.h"

//a function where the inputs are two matrices and the output is a boolean (1 of the matrices are equivalent or 0 otherwise)
int Equal_matrixes(double mat1[N][N], double mat2[N][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (fabs(mat1[i][j] - mat2[i][j] > EPSILON))
            {
                return 0;
            }
        }
    }
    return 1;
}

//generate a matrix with random values
void Generate_matrix(char *prompt, double mat[N][N])
{
    srand(time(NULL));
    int i, j;

    printf("%s\n", prompt);
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            mat[i][j] = rand();
}

//calculating the best time (we find the minimum from an array of type double)
double min(double x[], int size)
{
    double min=x[0];
    for (int i=1; i<size; i++)
    {
        if (x[i]<min)
        {
            min=x[i];
        }
    }
    return min;
}

//when we have all of the computed time we want to find out what is the best time with the minimum number of threads
void perfect_value(double *cpu_time_used_blocked)
{
    double sum=0;
    for(int i=0; i<10; i++){sum+=cpu_time_used_blocked[i];}
    double mean=sum/10;

    double closest_value=cpu_time_used_blocked[0];
    double min_diff=fabs(cpu_time_used_blocked[0] - mean);
    int closest_index=0;
    for (int i=1; i<10; i++)
    {
        double diff=fabs(cpu_time_used_blocked[i]-mean);
        if (diff<min_diff)
        {
            min_diff=diff;
            closest_value=cpu_time_used_blocked[i];
            closest_index=i;
        }
    }

    printf("The mean is %.6f\n", mean);
    printf("The closest value to the mean is %.3f at the index, so the best number of threads is %d.\n", closest_value, closest_index+1);
}

//a funtion where we can see the calculation of the times of every serial function (except the 'blocked' one)
void time_serial_functions(clock_t *start, clock_t *end, double *cpu_time_used)
{
    //serial functions
    printf("\nComputing time for serial_multiply_ijk...\n");
    start[0]=clock();
    serial_multiply_ijk();
    end[0]=clock();
    cpu_time_used[0]=((double)(end[0]-start[0]))/CLOCKS_PER_SEC;

    printf("Computing time for serial_multiply_ikj...\n");
    start[1]=clock();
    serial_multiply_ikj();
    end[1]=clock();
    cpu_time_used[1]=((double)(end[1]-start[1]))/CLOCKS_PER_SEC;

    printf("Computing time for serial_multiply_jik...\n");
    start[2]=clock();
    serial_multiply_jik();
    end[2]=clock();
    cpu_time_used[2]=((double)(end[2]-start[2]))/CLOCKS_PER_SEC;

    printf("Computing time for serial_multiply_jki...\n");
    start[3]=clock();
    serial_multiply_jki();
    end[3]=clock();
    cpu_time_used[3]=((double)(end[3]-start[3]))/CLOCKS_PER_SEC;

    printf("Computing time for serial_multiply_kij...\n");
    start[4]=clock();
    serial_multiply_kij();
    end[4]=clock();
    cpu_time_used[4]=((double)(end[4]-start[4]))/CLOCKS_PER_SEC;

    printf("Computing time for serial_multiply_kji...\n");
    start[5]=clock();
    serial_multiply_kji();
    end[5]=clock();
    cpu_time_used[5]=((double)(end[5]-start[5]))/CLOCKS_PER_SEC;

    printf("List of serial function times (in seconds):\n");
    printf("Serial_multiply_ijk: %f\n", cpu_time_used[0]);
    printf("Serial_multiply_ikj: %f\n", cpu_time_used[1]);
    printf("Serial_multiply_jik: %f\n", cpu_time_used[2]);
    printf("Serial_multiply_jki: %f\n", cpu_time_used[3]);
    printf("Serial_multiply_kij: %f\n", cpu_time_used[4]);
    printf("Serial_multiply_kji: %f\n", cpu_time_used[5]);
    
    printf("The best serial time is kept by: ");
    if(cpu_time_used[0]==min(cpu_time_used, sizeof(cpu_time_used)/sizeof(cpu_time_used[0]))) {printf("Serial_multiply_ijk\n");}
    if(cpu_time_used[1]==min(cpu_time_used, sizeof(cpu_time_used)/sizeof(cpu_time_used[0]))) {printf("Serial_multiply_ikj\n");}
    if(cpu_time_used[2]==min(cpu_time_used, sizeof(cpu_time_used)/sizeof(cpu_time_used[0]))) {printf("Serial_multiply_jik\n");}
    if(cpu_time_used[3]==min(cpu_time_used, sizeof(cpu_time_used)/sizeof(cpu_time_used[0]))) {printf("Serial_multiply_jki\n");}
    if(cpu_time_used[4]==min(cpu_time_used, sizeof(cpu_time_used)/sizeof(cpu_time_used[0]))) {printf("Serial_multiply_kij\n");}
    if(cpu_time_used[5]==min(cpu_time_used, sizeof(cpu_time_used)/sizeof(cpu_time_used[0]))) {printf("Serial_multiply_kji\n");}    
}

//a funtion where we can see the calculation of the times of every parallel function (except the 'blocked' one)
void time_parallel_functions(clock_t *start, clock_t *end, double *cpu_time_used)
{
    //parallel functions
    printf("\nComputing time for parallel_multiply_ijk...\n");
    start[0]=clock();
    parallel_multiply_ijk(50, N);
    end[0]=clock();
    cpu_time_used[0]=((double)(end[0]-start[0]))/CLOCKS_PER_SEC;
    
    printf("Computing time for parallel_multiply_ikj...\n");
    start[1]=clock();
    parallel_multiply_ikj(50, N);
    end[1]=clock();
    cpu_time_used[1]=((double)(end[1]-start[1]))/CLOCKS_PER_SEC;

    printf("Computing time for parallel_multiply_jik...\n");
    start[2]=clock();
    parallel_multiply_jik(50, N);
    end[2]=clock();
    cpu_time_used[2]=((double)(end[2]-start[2]))/CLOCKS_PER_SEC;

    printf("Computing time for parallel_multiply_jki...\n");
    start[3]=clock();
    parallel_multiply_jki(50, N);
    end[3]=clock();
    cpu_time_used[3]=((double)(end[3]-start[3]))/CLOCKS_PER_SEC;

    printf("Computing time for parallel_multiply_kij...\n");
    start[4]=clock();
    parallel_multiply_kij(50, N);
    end[4]=clock();
    cpu_time_used[4]=((double)(end[4]-start[4]))/CLOCKS_PER_SEC;

    printf("Computing time for parallel_multiply_kji...\n");
    start[5]=clock();
    parallel_multiply_kji(50, N);
    end[5]=clock();
    cpu_time_used[5]=((double)(end[5]-start[5]))/CLOCKS_PER_SEC;

    printf("List of parallel function times (in seconds):\n");
    printf("Parallel_multiply_ijk: %f\n", cpu_time_used[0]);
    printf("Parallel_multiply_ikj: %f\n", cpu_time_used[1]);
    printf("Parallel_multiply_jik: %f\n", cpu_time_used[2]);
    printf("Parallel_multiply_jki: %f\n", cpu_time_used[3]);
    printf("Parallel_multiply_kij: %f\n", cpu_time_used[4]);
    printf("Parallel_multiply_kji: %f\n", cpu_time_used[5]);

    printf("The best parallel time is held by: ");
    if(cpu_time_used[0]==min(cpu_time_used, sizeof(cpu_time_used)/sizeof(cpu_time_used[0]))) {printf("Parallel_multiply_ijk\n");}
    if(cpu_time_used[1]==min(cpu_time_used, sizeof(cpu_time_used)/sizeof(cpu_time_used[0]))) {printf("Parallel_multiply_ikj\n");}
    if(cpu_time_used[2]==min(cpu_time_used, sizeof(cpu_time_used)/sizeof(cpu_time_used[0]))) {printf("Parallel_multiply_jik\n");}
    if(cpu_time_used[3]==min(cpu_time_used, sizeof(cpu_time_used)/sizeof(cpu_time_used[0]))) {printf("Parallel_multiply_jki\n");}
    if(cpu_time_used[4]==min(cpu_time_used, sizeof(cpu_time_used)/sizeof(cpu_time_used[0]))) {printf("Parallel_multiply_kij\n");}
    if(cpu_time_used[5]==min(cpu_time_used, sizeof(cpu_time_used)/sizeof(cpu_time_used[0]))) {printf("Parallel_multiply_kji\n");}
}

//a funtion where we can see the calculation of the times of every blocked function
void blocked_functions(clock_t *start_blocked, clock_t *end_blocked, double *cpu_time_used_blocked)
{
    printf("\nComputing time for serial_blocked...\n");
    start_blocked[0]=clock();
    serial_blocked();
    end_blocked[0]=clock();
    cpu_time_used_blocked[0]=((double)(end_blocked[0]-start_blocked[0]))/CLOCKS_PER_SEC;

    printf("Computing time for parallel_blocked (the case when the size of the matrix is evenly divisible to the block size)...\n");
    start_blocked[1]=clock();
    parallel_blocked(50, N);
    end_blocked[1]=clock();
    cpu_time_used_blocked[1]=((double)(end_blocked[1]-start_blocked[1]))/CLOCKS_PER_SEC;

    printf("Computing time for parallel_blocked (the case when the size of the matrix is NOT evenly divisible to the block size)...\n");
    start_blocked[2]=clock();
    parallel_blocked(51, N);
    end_blocked[2]=clock();
    cpu_time_used_blocked[2]=((double)(end_blocked[2]-start_blocked[2]))/CLOCKS_PER_SEC;

    printf("List of times (in seconds):\n");
    printf("Serial_blocked: %.3f\n", cpu_time_used_blocked[0]);
    printf("Parallel_blocked (the case when the size of the matrix is evenly divisible to the block size): %.3f\n", cpu_time_used_blocked[1]);
    printf("Parallel_blocked (the case when the size of the matrix is NOT evenly divisible to the block size): %.3f\n", cpu_time_used_blocked[2]);
    printf("The best time is kept by: ");
    if (cpu_time_used_blocked[0] == min(cpu_time_used_blocked, sizeof(cpu_time_used_blocked)/sizeof(cpu_time_used_blocked[0]))) {printf("serial_blocked\n");}
    else if (cpu_time_used_blocked[1] == min(cpu_time_used_blocked, sizeof(cpu_time_used_blocked)/sizeof(cpu_time_used_blocked[0]))) {printf("parallel_blocked (even block size)\n");} 
    else if (cpu_time_used_blocked[2] == min(cpu_time_used_blocked, sizeof(cpu_time_used_blocked)/sizeof(cpu_time_used_blocked[0]))) {printf("parallel_blocked (uneven block size)\n");}

}

//we can notice in this function how the best block size for my computer is determined
void good_block_size(clock_t *start_blocked2, clock_t *end_blocked2, double *cpu_time_used_blocked2)
{
    printf("\n");
    for (int threads = 1; threads < 11; threads++)
    {
        start_blocked2[threads-1]=clock();
        parallel_blocked(threads, threads);
        end_blocked2[threads-1]=clock();
        cpu_time_used_blocked2[threads-1]=((double)(end_blocked2[threads-1]-start_blocked2[threads-1]))/CLOCKS_PER_SEC;
        printf("Number of threads: %d, CPU Time: %.3f seconds.\n", threads, cpu_time_used_blocked2[threads-1]);
    }

    perfect_value(cpu_time_used_blocked2);
}

//a function where we can find if the rest of the computed matrices are equal to classical i-j-k algorithm version
void comparing_matrix()
{
    serial_multiply_ijk();

    serial_multiply_ikj();
    if (Equal_matrixes(result_s, result_s2)) {printf("Serial ijk vs ikj: Matrices are equivalent.\n");}
    else {printf("Serial ijk vs ikj: Matrices are NOT equivalent.\n");}

    serial_multiply_jik();
    if (Equal_matrixes(result_s, result_s2)) {printf("Serial ijk vs jik: Matrices are equivalent.\n");} 
    else {printf("Serial ijk vs jik: Matrices are NOT equivalent.\n");}

    serial_multiply_jki();
    if (Equal_matrixes(result_s, result_s2)) {printf("Serial ijk vs jki: Matrices are equivalent.\n");}
    else {printf("Serial ijk vs jki: Matrices are NOT equivalent.\n");}

    serial_multiply_kij();
    if (Equal_matrixes(result_s, result_s2)) {printf("Serial ijk vs kij: Matrices are equivalent.\n");}
    else {printf("Serial ijk vs kij: Matrices are NOT equivalent.\n");}

    serial_multiply_kji();
    if (Equal_matrixes(result_s, result_s2)) {printf("Serial ijk vs kji: Matrices are equivalent.\n");}
    else {printf("Serial ijk vs kji: Matrices are NOT equivalent.\n");}

    parallel_multiply_ijk(50, N);
    if (Equal_matrixes(result_s, result_p)) {printf("Serial ijk vs Parallel ijk: Matrices are equivalent.\n");}
    else {printf("Serial ijk vs parallel ijk: Matrices are NOT equivalent.\n");}

    parallel_multiply_ikj(50, N);
    if (Equal_matrixes(result_s, result_p)) {printf("Serial ijk vs Parallel ikj: Matrices are equivalent.\n");} 
    else {printf("Serial ijk vs parallel ikj: Matrices are NOT equivalent.\n");}

    parallel_multiply_jik(50, N);
    if (Equal_matrixes(result_s, result_p)) {printf("Serial ijk vs Parallel jik: Matrices are equivalent.\n");} 
    else {printf("Serial ijk vs parallel jik: Matrices are NOT equivalent.\n");}

    parallel_multiply_jki(50, N);
    if (Equal_matrixes(result_s, result_p)) {printf("Serial ijk vs Parallel jki: Matrices are equivalent.\n");}
    else {printf("Serial ijk vs parallel jki: Matrices are NOT equivalent.\n");}

    parallel_multiply_kij(50, N);
    if (Equal_matrixes(result_s, result_p)) {printf("Serial ijk vs Parallel kij: Matrices are equivalent.\n");}
    else {printf("Serial ijk vs parallel kij: Matrices are NOT equivalent.\n");}

    parallel_multiply_kji(50, N);
    if (Equal_matrixes(result_s, result_p)) {printf("Serial ijk vs Parallel kji: Matrices are equivalent.\n");}
    else {printf("Serial ijk vs parallel kji: Matrices are NOT equivalent.\n");}


    serial_multiply_ijk();
    serial_blocked();
    if (Equal_matrixes(result_s, result_s2)) {printf("Serial ijk vs serial blocked: Matrices are equivalent.\n");}
    else {printf("Serial ijk vs Parallel blocked: Matrices are NOT equivalent.\n");}

    parallel_blocked(50, N);
    if (Equal_matrixes(result_s, result_p2)) {printf("Serial ijk vs parallel blocked: Matrices are equivalent.\n");}
    else {printf("Serial blocked vs Parallel blocked: Matrices are NOT equivalent.\n");}
}

//main fucntion
int main(void)
{
    printf("NUMBER OF ROWS AND COLUMNS USED: %d * %d.\n", N, N);
    Generate_matrix("Generating matrix a...", a);
    Generate_matrix("Generating matrix b...", b);
    clock_t start[6];
    clock_t end[6];
    double cpu_time_used[6];
    time_serial_functions(start, end, cpu_time_used);
    time_parallel_functions(start, end, cpu_time_used);

    clock_t start_blocked[3];
    clock_t end_blocked[3];
    double cpu_time_used_blocked[3];
    blocked_functions(start_blocked, end_blocked, cpu_time_used_blocked);
    
    clock_t start_blocked2[10];
    clock_t end_blocked2[10];
    double cpu_time_used_blocked2[10];
    good_block_size(start_blocked2, end_blocked2, cpu_time_used_blocked2);

    comparing_matrix();
    return 0;
}