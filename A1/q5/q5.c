#include <stdio.h>
#include <omp.h>

// variables
const long num_steps = 100000;
double step;
const long max_num_threads = 100;

// Pi calculation seriable execution
// returns time of execution
double piSerial() {
    double start_time = omp_get_wtime();
    long i;
    double x, pi, sum = 0.0;
    step = 1.0/(double)num_steps;
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0/(1.0+ x*x);
    }
    pi = step * sum;
    double time = omp_get_wtime() - start_time;
    printf("Pi: %lf\n", pi);
    return time;
}

// Pi calculation parallel execution with N threads
// returns time of execution
double piParallel(long nthreads) {
    double start_time = omp_get_wtime();
    // =================
    int i;
    double pi, sum = 0.0;
    step = 1.0/(double)num_steps;
    #pragma omp parallel num_threads(nthreads) 
    {
        double partial_sum = 0, x;
        long i, id;
        id = omp_get_thread_num();
        // calculation
        for(i = id; i < num_steps; i += nthreads) {
            x = (i + 0.5) * step;
            partial_sum += 4.0/(1.0+ x*x);
        }
        #pragma omp critical
        sum = sum + partial_sum;
    }
    pi = step * sum;
    // =================
    double time = omp_get_wtime() - start_time;
    printf("Pi: %lf\n ", pi);
    return time;
}   


int main() {

    // serial
    double serial_time = piSerial();
    printf("Serial Execution Time: %lf\n", serial_time);

    // parallel
    double res[max_num_threads+1];
    printf("Parallel Execution Time: \n");
    for (long i = 2; i <= max_num_threads; i*=2) {
        res[i] = piParallel(i); 
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
