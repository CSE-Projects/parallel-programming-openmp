#include "omp.h" /* OpenMP compiler directives, APIs are declared here */

void printHelloWorld(int threadId) {
    printf("Hello World: %d\n", threadId);
}

void main() {
    /* Parallel region begins here */
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printHelloWorld(id);
    }
}