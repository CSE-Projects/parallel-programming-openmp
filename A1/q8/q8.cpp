#include <bits/stdc++.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

// Size of dynamically allocated array
long long int NUM = 100000;

// Producer
void fill_rand(int N, long double *A)
{
    // Filling random values
	for (int i=0; i<N; i++)
    {
        // A[i] = 1;
		A[i] = ((long double) (rand()%10000))/100.0;
    }
    return;
}

// Consumer
long double Sum_array(int N, long double *A)
{
    // Calculating the sum
	long double sum = 0.0;
	for (int i=0; i<N; i++)
	{
    	sum+=A[i];
    }
    return sum;
}


int main()
{
    // Seeding PRNG with time
    srand(time(NULL));

	long double *array, sum = 0.0, runtime;

    // Default flag is kept false
	bool flag = false;

    // Allocating memory
    array = new long double[NUM];

    // Initializing the timer
	runtime = omp_get_wtime();
    omp_set_num_threads(2);
	#pragma omp parallel shared(array,sum,flag)
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				fill_rand(NUM,array);
				#pragma omp flush
				flag = true;
				if(flag==true)
				{
					#pragma omp flush(flag)
				}
			}
			#pragma omp section
			{
				while (flag==false)
				{
					#pragma omp flush(flag)
				}
				#pragma omp flush
				sum = Sum_array(NUM,array);
			}
	 	}
	}

    // Stop timer
	runtime = omp_get_wtime() - runtime;

    // Printing sum along with answer
	cout<<fixed<<setprecision(5)<<"Time = "<<runtime<<", Sum = "<<sum<<"\n";

    return 0;
}