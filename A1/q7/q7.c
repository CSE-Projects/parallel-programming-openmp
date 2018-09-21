#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

// variables
const long num_steps = 1000000;
const long max_num_threads = 100;
const long radius = 100000;
const double center_x = 1, center_y = 1;

// Pi calculation Monte Carlo seriable execution
// returns time of execution
double piMcSerial() {
    double start_time = omp_get_wtime();
    //=====================
    double x, y, diameter, pi;
	double count = 0;
    srand(time(0)); 
	for (long i = 0; i < num_steps; ++i) {
		x = (double)(rand()%radius - 1);
		y = (double)(rand()%radius - 1);
		diameter = sqrt((x - center_x)*(x - center_x) + (y - center_y)*(y - center_y));
		if(diameter <= radius) {
			count++;
		}
	}
	pi = 4.0*count/num_steps;
    ///=====================
    double time = omp_get_wtime() - start_time;
    printf("Pi: %lf\n", pi);
    return time;
}

// Pi calculation Monte Carlo parallel execution with N threads
// returns time of execution
double piMcParallel(long nthreads) {
    double start_time = omp_get_wtime();
    // =================
    double x, y, pi, diameter;
	double count;
    srand(time(0)); 
    #pragma omp parallel for private(x, y, diameter) reduction(+:count) num_threads(nthreads)
    for(long i = 0; i < num_steps; ++i) {
        x = (double)(rand()%radius - 1);
        y = (double)(rand()%radius - 1);
        diameter = sqrt((x - center_x)*(x - center_x) + (y - center_y)*(y - center_y));
        if(diameter <= radius) {
            count++;
        }
    }
    pi = 4.0*count/num_steps; 
    // =================
    double time = omp_get_wtime() - start_time;
    printf("Pi: %lf\n ", pi);
    return time;
}   


int main() {

    // serial
    double serial_time = piMcSerial();
    printf("Serial Execution Time: %lf\n", serial_time);

    // parallel
    double res[max_num_threads+1];
    printf("Parallel Execution Time: \n");
    for (long i = 2; i <= max_num_threads; i*=2) {
        res[i] = piMcParallel(i); 
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
