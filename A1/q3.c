#include <stdio.h>
#include <omp.h>

// variables
#define N 1000000
#define A 2
double X[N];
double Y[N];
double Z[N];

// DAXPY seriable execution
// returns time of execution
double daxpySerial() {
    double start_time = omp_get_wtime();
    // printf("Result Serial: \n");
    //=================
    for (long i = 0; i < N; i++) {
        Z[i] = A*X[i] + Y[i];
        // printf("%lf ", X[i]);
    }
    //=================
    // printf("\n");
    return omp_get_wtime() - start_time;
}

// DAXPY parallel execution with N threads
// returns time of execution
double daxpyParallel(long nthreads) {
    double start_time = omp_get_wtime();
    // =================
    #pragma omp parallel num_threads(nthreads) 
    {
        #pragma omp for
        for(long i = 0; i < N; i++) {
            Z[i] = A*X[i] + Y[i];
        }
    }
    // =================
    double time =  omp_get_wtime() - start_time;

    // if (nthreads == N) {
    //     printf("Result Parallel: \n");
    //     for (long i = 0; i < N; i++) {
    //         printf("%lf ", X[i]);
    //     }
    //     printf("\n");
    // }

    return time;
} 

// set values for X and Y
void setXY () {
    for (long i = 0; i < N; i++) {
        X[i] = Y[i] = i;
    }
}

int main() {
    // set values for X and Y
    setXY();

    // serial
    double serial_time = daxpySerial();
    printf("Serial Execution Time: %lf\n", serial_time);

    // parallel
    double res[N+1];
    printf("Parallel Execution Time: \n");
    for (long i = 2; i <= N; i++) {
        res[i] = daxpyParallel(i); 
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
