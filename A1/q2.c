#include "omp.h" /* OpenMP compiler directives, APIs are declared here */

void printHelloWorld(int threadId) {
    printf("Hello World: %d\n", threadId);
}

void main() {
    double start_time = omp_get_wtime();
    /* Parallel region begins here */
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printHelloWorld(id);
    }
    double time_parallel =  omp_get_wtime() - start_time;

    printf("Serial\n");
    start_time = omp_get_wtime();
    // serial 4 times 
    for (int i = 0; i < 4; i++) {
        printHelloWorld(i);
    }
    double time_serial =  omp_get_wtime() - start_time;

    // results
    printf("Parallel time: %lf\n", time_parallel);
    printf("Serial time: %lf\n", time_serial);
}