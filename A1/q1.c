#include "omp.h" /* OpenMP compiler directives, APIs are declared here */

void main() {
    double start_time = omp_get_wtime();
    /* Parallel region begins here */
    #pragma omp parallel
    {
        printf("Hello World\n");
    }
    double time_parallel =  omp_get_wtime() - start_time;

    printf("Serial\n");
    start_time = omp_get_wtime();
    // serial 4 times
    for (int i = 0; i < 4; i++) {
        printf("Hello World\n");
    }
    double time_serial =  omp_get_wtime() - start_time;
    
    // results
    printf("Parallel time: %lf\n", time_parallel);
    printf("Serial time: %lf\n", time_serial);
}