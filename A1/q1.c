#include "omp.h" /* OpenMP compiler directives, APIs are declared here */

void main() {
    /* Parallel region begins here */
    #pragma omp parallel
    {
        printf("Hello World\n");
    }
}