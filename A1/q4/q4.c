#include <stdio.h>
#include <omp.h>

// variables
#define N 500
#define M 500
#define K 500
double A[N][M];
double B[M][K];
double C[N][K];

// Matrix Mul seriable execution
// returns time of execution
double matrixMulSerial() {
    double start_time = omp_get_wtime();
    for (long i = 0; i < N; i++) {
        for (long k = 0; k < K; k++) {
            C[i][k] = 0;
            for (long j = 0; j < M; j++) {
                C[i][k] += A[i][j] * B[j][k]; 
            }
        }
    }
    double time = omp_get_wtime() - start_time;

    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < K; j++) {
    //         printf("%lf ", C[i][j]);
    //     }
    //     printf("\n");
    // } 
    return time;
}

// Matric Mul parallel execution with N threads
// returns time of execution
double matrixMulParallel(long nthreads) {
    double start_time = omp_get_wtime();
    // =================
    #pragma omp parallel num_threads(nthreads) 
    {   
        for (long i = 0; i < N; i++) {
            for (long k = 0; k < K; k++) {
                C[i][k] = 0;
                for (long j = 0; j < M; j++) {
                    C[i][k] += A[i][j] * B[j][k]; 
                }
            }
        }
        
    }
    // =================
    double time = omp_get_wtime() - start_time;

    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < K; j++) {
    //         printf("%lf ", C[i][j]);
    //     }
    //     printf("\n");
    // } 
    return time;
}   

// set values for A and B
void setAB () {
    for (long i = 0; i < N; i++) {
        for (long j = 0; j < M; j++) {
            A[i][j] = i+j;
        }
    }

    for (long i = 0; i < M; i++) {
        for (long j = 0; j < K; j++) {
            B[i][j] = i+j;
        }
    }
}

int main() {
    // set values for X and Y
    setAB();

    // serial
    double serial_time = matrixMulSerial();
    printf("Serial Execution Time: %lf\n", serial_time);

    // parallel
    double res[N+1];
    printf("Parallel Execution Time: \n");
    for (long i = 2; i <= N; i*=2) {
        res[i] = matrixMulParallel(i); 
        printf("#threads: %ld time: %lf\n", i, res[i]);
    }

    // display results
    // printf("Serial Execution Time: %lf\n", serial_time);
    // printf("Parallel Execution Time: \n");
    // for (long i = 2; i <= N; i++) {
    //     printf("#threads: %d time: %lf\n", i, res[i]);
    // }
    
    return 0;
}
