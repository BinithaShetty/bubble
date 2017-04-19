#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
        int i, n, temp;
	int nextLoop;
	clock_t t;
        printf("Enter the number of elements:");
   	scanf("%d",&n);
	int *x = (int*) malloc(n * sizeof(int));
	srand(time(NULL));
	for (i = 0; i <  n; i++)
		x[i] = (int)rand()/((int)RAND_MAX/100);     
	
	for (i = 0; i <  n; i++)
		printf("%d ",x[i]);
    	nextLoop = 1;
    	t = clock();
    	while(nextLoop)
    	{
    	#pragma omp parallel private(temp)
    	{
            nextLoop = 0;
            #pragma omp for \
                    reduction(+:nextLoop)
            for(i = 0; i < n - 1; i = i + 2) //all the even i's
            {
                    if(x[i] > x[i+1] )
                    {
                            temp = x[i];
                            x[i] = x[i+1];
                            x[i+1] = temp;
                            nextLoop=1;
                    }
            }
            #pragma omp for \
                    reduction(+:nextLoop)
	    for(i = 1; i < n - 1; i = i + 2) //all the odd i's
            {
                    if( x[i] > x[i+1] )
                    {
                            temp = x[i];
                            x[i] = x[i+1];
                            x[i+1] = temp;
                            nextLoop=1;
                    }
            }
    	}
    	}
    
    	t = clock() - t;
    	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    	printf("\nparallel bubble() took %f seconds to execute \n", time_taken);

    	for (i = 0; i <  n; i++)
		printf("%d ",x[i]);

    	return 0;
}


